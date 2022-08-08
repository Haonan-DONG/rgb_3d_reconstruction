#include "include/exe.h"

hash_t hash_run_time(const char *str)
{
    hash_t ret = basis;

    while (*str)
    {
        ret ^= *str;
        ret *= prime;
        str++;
    }

    return ret;
}

constexpr hash_t hash_compile_time(const char *str, hash_t last_value = basis)
{
    return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}

constexpr hash_t operator"" _hash(const char *p, size_t)
{
    return hash_compile_time(p);
}

void print_help()
{
    std::cout << "Reconstruction help information: " << endl
              // Help and other usage.
              << "  -h --help               --Show help information." << endl
              << "  AutomaticReconstructor  --Automatically reconstruct sparse and dense model for a set of input images. " << endl

              // get FeatureExtractor
              << "  FeatureExtractor        --Perform feature extraction for a set of images. " << endl

              // Matcher Strategy
              << "  ExhaustiveMatcher       --Perform feature matching after performing feature extraction. " << endl
              << "  SequentialMatcher       --Perform feature matching applying to sequential images. " << endl
              << "  SpatialMatcher          --Perform Spatial Matching Strategy with GPS file." << endl

              // Sparse Reconstruction
              << "  SFM                     --Sparse 3D reconstruction / mapping of the dataset using SfM after performing feature extraction and matching. " << endl

              // Image Undistortion
              << "  ModelConverter          --Convert the output into Bundler, VisualSFM and other format. " << endl
              << "  ImageUndistorter        --Output undistorted images. " << endl

              // MVS
              << "  DensifyPointCloud       --Densify sparse point cloud. " << endl
              << "  InterfaceDense          --bridge the point cloud to mesh from exist dense algorithm." << endl

              // Mesh
              << "  ReconstructMesh         --Rough mesh reconstruction. " << endl

              // Texture
              << "  TextureMesh             --Texture refined mesh. " << endl
              << "  TextureMapping          --Texture mesh. " << endl;
}

char **get_argv(int argc, char *argv[])
{
    char **new_argv = new char *[10];
    new_argv[0] = argv[0];
    for (int i = 1; i < argc - 1; i++)
    {
        new_argv[i] = argv[i + 1];
    }
    return new_argv;
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argv[1] == "--help" || argv[1] == "-h")
    {
        print_help();
    }
    if (argc >= 2)
    {
        char *command = argv[1];
        switch (hash_run_time(command))
        {
        case "AutomaticReconstructor"_hash:
            std::cout << "performing AutomaticReconstructor" << endl;
            std::cout << "performing FeatureExtractor" << endl;
            argv[1] = "feature_extractor";
            ThreeDProcess(argc, argv);
            std::cout << "performing ExhaustiveMatcher" << endl;
            argv[1] = "exhaustive_matcher";
            ThreeDProcess(argc, argv);
            std::cout << "performing SFM" << endl;
            argv[1] = "mapper";
            ThreeDProcess(argc, argv);
            std::cout << "performing ImageUndistortion" << endl;
            argv[1] = "image_undistorter";
            ThreeDProcess(argc, argv);
            argv[1] = "InterfaceDense";
            argv[2] = "-i";
            InterfaceDense(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            std::cout << "performing DensifyPointCloud" << endl;
            argv[1] = "DensifyPointCloud";
            DensifyPointCloud(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            std::cout << "performing ReconstructMesh" << endl;
            argv[1] = "ReconstructMesh";
            ReconstructMesh(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            std::cout << "performing TextureMesh" << endl;
            TextureMesh(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            break;
        case "TextureMesh"_hash:
            std::cout << "performing TextureMesh" << endl;
            TextureMesh(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            break;
        case "ReconstructMesh"_hash:
            std::cout << "performing ReconstructMesh" << endl;
            ReconstructMesh(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            break;
        case "DensifyPointCloud"_hash:
            std::cout << "performing DensifyPointCloud" << endl;
            DensifyPointCloud(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            break;
        case "InterfaceDense"_hash:
            std::cout << "performing InterfaceDense" << endl;
            InterfaceDense(argc - 1, (LPCTSTR *)get_argv(argc, argv));
            break;
        case "FeatureExtractor"_hash:
            std::cout << "performing FeatureExtractor" << endl;
            argv[1] = "feature_extractor";
            ThreeDProcess(argc, argv);
            break;
        case "FeatureImporter"_hash:
            std::cout << "performing FeatureImporter" << endl;
            argv[1] = "feature_importer";
            ThreeDProcess(argc, argv);
            break;
        case "ExhaustiveMatcher"_hash:
            std::cout << "performing ExhaustiveMatcher" << endl;
            argv[1] = "exhaustive_matcher";
            ThreeDProcess(argc, argv);
            break;
        case "SFM"_hash:
            std::cout << "performing SFM" << endl;
            argv[1] = "mapper";
            ThreeDProcess(argc, argv);
            break;
        case "HierarchicalMapper"_hash:
            std::cout << "performing hierarchical_mapper" << endl;
            argv[1] = "hierarchical_mapper";
            ThreeDProcess(argc, argv);
            break;
        case "PointTriangulator"_hash:
            std::cout << "performing point trianguation" << std::endl;
            argv[1] = "point_triangulator";
            ThreeDProcess(argc, argv);
        case "ModelConverter"_hash:
            std::cout << "performing ModelConverter" << endl;
            argv[1] = "model_converter";
            ThreeDProcess(argc, argv);
            break;
        case "SequentialMatcher"_hash:
            std::cout << "performing SequentialMatcher" << endl;
            argv[1] = "sequential_matcher";
            ThreeDProcess(argc, argv);
            break;
        case "ImageUndistorter"_hash:
            std::cout << "performing ImageUndistorter" << endl;
            argv[1] = "image_undistorter";
            ThreeDProcess(argc, argv);
            break;
        case "TextureMapping"_hash:
            std::cout << "performing TextureMapping" << endl;
            TextureMapping(argc - 1, get_argv(argc, argv));
            break;
        case "SpatialMatcher"_hash:
            std::cout << "performing SpatialMatcher" << endl;
            argv[1] = "spatial_matcher";
            ThreeDProcess(argc, argv);
            break;
        default:
            print_help();
            break;
        }
    }
}
