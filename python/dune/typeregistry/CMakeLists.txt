add_python_targets(typeregistry
  __init__
)
dune_add_pybind11_module(NAME _typeregistry)
install(TARGETS _typeregistry LIBRARY DESTINATION python/dune/typeregistry)
