# 逐层构建库
add_subdirectory(domain)
add_subdirectory(app)
add_subdirectory(infrastructure)
add_subdirectory(presentation)
add_subdirectory(cli)           # CLI 组合根（库，不含 main）

