# Contents

* [overview](#overview)
    - [介绍](#1.0-introduction)
        - [命名](#1.1-命名)
        - [作用](#1.2-作用)
    - [文件目录缓存](#2.0-Directory-Entry-Cache-(dcache)-文件目录缓存)


# overview

## 1.0 introduction

### 1.1 命名
The Virtual File System (also known as the Virtual Filesystem Switch)
提供
  
### 1.2 作用
the software layer in the kernel that provides the filesystem interface to userspace programs.
给APP提供文件系统接口。  

provides an abstraction within the kernel which allows different filesystem implementations to coexist.
在内核提供一种抽象，使不同的文件系统实现能够共存。

## 2.0 Directory Entry Cache (dcache) 文件目录缓存

### Function
The VFS implements the open(2), stat(2), chmod(2), and similar system calls. The pathname argument that is passed to them is used by the VFS to search through the directory entry cache (also known as the dentry cache or dcache) This provides a very fast look-up mechanism to translate a pathname (filename) into a specific dentry. Dentries live in RAM and are never saved to disc: they exist only for performance.  
提供一种非常块的查找机制；把文件名的路径转换为特定的文件夹目录。这些文件目录存在内存RAM中；并且不会保存到磁盘：他们的存在只是为了执行效率。

### implemetaiton details
The dentry cache is meant to be a view into your entire filespace. As most computers cannot fit all dentries in the RAM at the same time, some bits of the cache are missing. In order to resolve your pathname into a dentry, the VFS may have to resort to creating dentries along the way, and then loading the inode. This is done by looking up the inode.  
文件目录缓存是对文件空间的缩略图。文件目录缓存并不所有的缓存都能一直存在，也有一些cache会被回收。所以在查找的过程中；会创建目录缓存然后开始查找inode



