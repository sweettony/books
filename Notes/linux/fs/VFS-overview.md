# Contents

* [overview](#overview)
    - [介绍](#1.0-introduction)
        - [命名](#命名)
        - [作用](#作用)
    - [文件目录缓存](#2.0-Directory-Entry-Cache-(dcache)-文件目录缓存)
    - [inode 结点](#3.0-The-inode-object)
    - [file  结构](#4.0-The-file-object)


# overview

## 1.0 introduction

### 命名
>The Virtual File System (also known as the Virtual Filesystem Switch)
提供
  
### 作用
>the software layer in the kernel that provides the filesystem interface to userspace programs.
给APP提供文件系统接口。  
provides an abstraction within the kernel which allows different filesystem implementations to coexist.
在内核提供一种抽象，使不同的文件系统实现能够共存。

## 2.0 Directory Entry Cache (dcache) 文件目录缓存

### Function
>The VFS implements the open(2), stat(2), chmod(2), and similar system calls. The pathname argument that is passed to them is used by the VFS to search through the directory entry cache (also known as the dentry cache or dcache) This provides a very fast look-up mechanism to translate a pathname (filename) into a specific dentry. Dentries live in RAM and are never saved to disc: they exist only for performance.  
提供一种非常块的查找机制；把文件名的路径转换为特定的文件夹目录。这些文件目录存在内存RAM中；并且不会保存到磁盘：他们的存在只是为了执行效率。

### implemetaiton details
>The dentry cache is meant to be a view into your entire filespace. As most computers cannot fit all dentries in the RAM at the same time, some bits of the cache are missing. In order to resolve your pathname into a dentry, the VFS may have to resort to creating dentries along the way, and then loading the inode. This is done by looking up the inode.  
文件目录缓存是对文件空间的缩略图。文件目录缓存并不所有的缓存都能一直存在，也有一些cache会被回收。所以在查找的过程中；会创建目录缓存然后开始查找inode

## 3.0 The inode object

### what is inode? and where is inode?
>An individual dentry usually has a pointer to an inode. Inodes are filesystem objects such as regular files, directories, FIFOs and other beasts. They live either on the disc (for block device filesystems) or in the memory (for pseudo filesystems).  
一个单独的文件目录通常有一个inode指针。inode 是文件系统的对象；比如：普通文件，文件目录， 队列等等。inode保存在磁盘或者内存里。  

### implemetaion details
>To look up an inode requires that the VFS calls the lookup() method of the parent directory inode. This method is installed by the specific filesystem implementation that the inode lives in. Once the VFS has the required dentry (and hence the inode), we can do all those boring things like open(2) the file, or stat(2) it to peek at the inode data. The stat(2) operation is fairly simple: once the VFS has the dentry, it peeks at the inode data and passes some of it back to userspace.  
查找一个inode结点需要VFS调用父类的文件目录结点的lookup()，这个函数是被特定的文件系统安装的。当获取到文件目录（同时也是inode时），我们就可以调用open()等系统函数。

## 4.0 The file object
> Opening a file requires operations  
1. allocation of a file structure (this is the kernel-side implementation of file descriptors).  
2. The freshly allocated file structure is initialized with a pointer to the dentry and a set of file operation member functions. These are taken from the inode data.  
第一步需要分配file的内存。  
第二步需要把获得的inode结点对file结构初始化。

>The open() file method is then called so the specific filesystem implementation can do its work. You can see that this is another switch performed by the VFS. The file structure is placed into the file descriptor table for the process.  
最后open函数被调用，所以不同的文件系统都能工作。你可以看到这是另一个**VFS**的转换。分配出来的file struct会被放到相应**进程的file descriptor table**。




