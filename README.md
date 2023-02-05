# rgb_3d_reconstruction_pipeline

To help to learn the 3d reconstruction from rgb input, here I give sdk and lib to help you make a textured mesh from only rgb images from the traditional methods.

## Environment.
```shell
# ubuntu 18.04
# install Liblz4-dev, libmetis-dev.

# use high version cmake (here we use cmake 3.22)
/home/mvs18/Downloads/cmake-3.22.5-linux-x86_64/bin/cmake .. -DCMAKE_CUDA_ARCHITECTURES='86'
```

## TODO
- [ ] First version Lib for using.

## Architectures
### Sparse Reconstruction


## Test Machines
- [ ] GoPro
- [ ] Binocular Stereo
- [ ] Phone Camera

## Acknowledgements
- [COLMAP](https://github.com/colmap/colmap)
- [OpenMVS](https://github.com/cdcseacave/openMVS)
- [Poisson Reconstruction](https://www.cs.jhu.edu/~misha/Code/PoissonRecon/Version13.8/)
- [Meshlab](https://github.com/cnr-isti-vclab/meshlab)