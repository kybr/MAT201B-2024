set(app_include_dirs /opt/homebrew/Cellar/pytorch/2.1.2_1/libexec/lib/python3.11/site-packages/torch/include/torch/csrc/api/include)
set(app_link_libs torch c10 torch_global_deps shm torch_cpu)
set(app_linker_flags -L/opt/homebrew/Cellar/pytorch/2.1.2_1/libexec/lib/python3.11/site-packages/torch/lib)
