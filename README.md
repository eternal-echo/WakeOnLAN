# 使用

## 环境
cmake

boost：
```bash
sudo apt-get install libboost-all-dev
```

## 配置
复制`include/config.h.example`为`include/config.h`，并修改其中的配置项，设置默认的IP地址和MAC地址。

## 构建

通过创建构建目录（如 `build/`），运行 `cmake` 生成构建文件，然后使用 `make` 构建目标。

示例命令：

```bash
# WSL或ubuntu环境
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
./main
make test      # 编译并运行测试代码
```

## 测试
在build目录下，运行命令行，观察是否成功唤醒：
```bash
./cli -m 00:00:00:00:00:00 -i 192.168.1.10
```