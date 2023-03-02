# rgb_3d_reconstruction
## Purpose
- A handy pipeline to make a textured mesh from rgb images (currently) by the traditional methods.
- Reproduce the latest methods.


## Data configuration
```
-- test
    -- images      --> Image and camera prior information.
        -- 00000000.jpg
        -- 00000001.jpg
        ...
        -- 00000333.jpg
    -- sfm         --> Undistorted images, poses and optimized intrinsics.
    -- mvs         --> Depth map and fused point cloud.
    -- mesh        --> Textured and un-textured mesh.
```

## TODO
- [X] Released Pipeline for COLMAP and openMVS as a library. From rgb input into textured mesh.
- [ ] Combine Poisson Reconstruction.
- [ ] Add keyframe abstraction from SLAM-Based algorithm.
- [ ] ACMM Re-coding.

## Samples
- [X] DTU-scan1
- [ ] GoPro
- [ ] Binocular Stereo
- [ ] Phone Camera

## Acknowledgements
- [COLMAP-3.8](https://github.com/colmap/colmap)
- [OpenMVS-2.0.1](https://github.com/cdcseacave/openMVS)
- [Poisson Reconstruction](https://www.cs.jhu.edu/~misha/Code/PoissonRecon/Version13.8/)
- [Meshlab](https://github.com/cnr-isti-vclab/meshlab)