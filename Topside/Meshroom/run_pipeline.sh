#!/bin/bash

# Stop the script immediately if any command fails
set -e

echo "=== STARTING STAGE 1: STREAM CAPTURE & AI PROCESSING ==="
docker run --rm --platform linux/amd64 \
  --memory="8g" --cpus="4" \
  -v "$(pwd):/workspace" \
  stream-capture-pipeline \
  /bin/bash -c "
    set -euo pipefail && \
    python3 test.py && \
    mkdir -p /workspace/output/colmap_workspace/sparse/0 && \
    if [ -f /workspace/output/colmap_workspace/sparse/cameras.bin ]; then \
      cp /workspace/output/colmap_workspace/sparse/*.bin /workspace/output/colmap_workspace/sparse/0/ 2>/dev/null || true; \
    fi && \
    colmap model_converter \
      --input_path /workspace/output/colmap_workspace/sparse/0 \
      --output_path /workspace/output/colmap_workspace/sparse \
      --output_type TXT
  "

echo "=== STARTING STAGE 2: 3D MESH GENERATION ==="
docker run --rm --platform linux/amd64 \
  -v "$(pwd)/images:/workspace/images" \
  -v "$(pwd)/output:/workspace/output" \
  openmvs/openmvs-ubuntu:latest \
  /bin/bash -c "
    set -euo pipefail && \
    mkdir -p /workspace/output/mvs_workspace && \
    
    mkdir -p /workspace/output/colmap_workspace/workspace/output/colmap_workspace
    
    cp -a /workspace/images/. /workspace/output/colmap_workspace/workspace/output/colmap_workspace/
    
    cd /workspace/output/mvs_workspace && \
    
    InterfaceCOLMAP \
      --input-file /workspace/output/colmap_workspace \
      --output-file scene.mvs \
      --image-folder /workspace/output/colmap_workspace \
      --archive-type -1 && \
      
    DensifyPointCloud \
      --input-file scene.mvs \
      --output-file scene_dense.mvs \
      --archive-type -1 && \
      
    ReconstructMesh \
      --input-file scene_dense.mvs \
      --output-file scene_dense_mesh.mvs \
      --archive-type -1 && \
      
    TextureMesh \
      --input-file scene_dense_mesh.mvs \
      --output-file scene_dense_mesh_texture.mvs \
      --export-type obj \
      --archive-type -1 && \
      
    cp /workspace/output/mvs_workspace/scene_dense_mesh_texture.obj /workspace/output/final_model.obj && \
    cp /workspace/output/mvs_workspace/scene_dense_mesh_texture.mtl /workspace/output/final_model.mtl && \

    ORIG_TEXT_FILE=\$(ls /workspace/output/mvs_workspace/scene_dense_mesh_texture_material_0_map_Kd.* 2>/dev/null | head -n 1) && \
    EXT=\"\${ORIG_TEXT_FILE##*.}\" && \
    
    cp \"\$ORIG_TEXT_FILE\" \"/workspace/output/final_model_material_0_map_Kd.\$EXT\" && \
    
    sed -i 's/scene_dense_mesh_texture.mtl/final_model.mtl/g' /workspace/output/final_model.obj && \
    
    sed -i 's/scene_dense_mesh_texture_material_0_map_Kd/final_model_material_0_map_Kd/g' /workspace/output/final_model.mtl
  "

echo "=== PIPELINE COMPLETE: final_model.obj IS READY ==="