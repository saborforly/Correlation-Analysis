# 关联数据分析

根据挑选后的 Index 数据加载分析时间窗口内的物理事例，通过减少数据读入提高关联事例分析的效率。输入为Index文件，输出为挑选后的关联数据。数据的处理流程如下图所示：  
![image](https://github.com/saborforly/Correlation-Analysis/blob/main/image/aam.png)
### 系统环境
offline version: J20v1r0-Pre2

### 部署
source setup.sh
* 编译OECEvent
pushd OECEvent/cmt
cmt coinfig
cmt make
popd
* 按照上述方式进行逐个package的编译
    * RootIO   
    * Tag/TagInfo
    * Tag/SniperMuster
    * Tag/IndexReader
    * Tag/IndexSelect
    * Tag/IndexEventIO
    * Tag/EventAna
    * Tag/EventWriter
    * Tag/DataGen
* 编译完成之后运行
    * Python Tag/run.py



### 0.管理多线程和全局缓存
SniperMuster主要负责线程的创建、调度和执行以及全局缓存中缓存区的定义，主要涉及的类如图所示:  
![image](https://github.com/saborforly/Correlation-Analysis/blob/main/image/sniperMuster.png)
* GlobalBuffer类主要负责的是全局缓存，主要包括两个链表：索引数据链表和窗口事例数据链表，各个线程都可以通过锁和状态量从全局缓存中获取数据和写入数据。在链表的实现中，为链表中的节点都设置了状态，状态的值代表着数据处理所处于的阶段  
![image](https://github.com/saborforly/Correlation-Analysis/blob/main/image/linkNode.png)

* ThreadAssistor类主要负责Sniper Task的初始化、执行和结束。
* TaskSupervisor 主要涉及到多线程的调度，例如事例挑选多线程和关联事例分析多线程
* GlobalStream 主要涉及到一些单线程的输出输出流，例如读取索引数据、加载物理事例等。


### 1.读取Index数据
IndexReader作为一个Task，主要负责读取索引数据，将数据转化为Hearder数据结构，保存在全局缓存（GlobalBuffer）的索引数据链表中。
* BeginReaderHdl服务类，继承接口IIncidentHandler
* IndexReaderMemMgr服务类，初始化和注册BeginReaderHdl
* 由于Index数据格式可以有很多种，因此提供了Index数据读取的接口IIndexReader，并实现了读取txt数据的类TxtIndexReader。

### 2.挑选Index数据
IndexSelect可以启动多个Task，主要负责多线程的索引数据的挑选，通过获取索引数据链表中保存的索引数据，使用单事例的挑选算法进行单事例的挑选。处理后的数据只需要修改链表节点状态值即可进行下一步的处理。
* BeginSelectHdl服务类，继承接口IIncidentHandler
* SelectMemMgr服务类，负责内存管理，初始化和注册BeginSelectHdl
* SelectStore由IDataBlock派生而来，提供了数据访问和缓存的能力
* SelectInputSvc 服务类，负责与GlobalBuffer进行交互，获取全局缓存中的数据
* FirstFilterAlg索引数据挑选算法

### 3.加载挑选后的Index数据相对应的物理事例和窗口事例
IndexEventIO作为一个Task，负责加载挑选后的索引数据相对应的物理事例以及该事例相邻的整个窗口的事例，然后将窗口数据按时间顺序，保存在全局缓存的窗口事例数据链表中。
* BeginIOHdl服务类，继承接口IIncidentHandler
* IndexEventIOMemMgr 服务类，负责物理事例加载任务的内存管理
* IOInputSvc 服务类，负责与GlobalBuffer进行交互，获取全局缓存中的数据
* WindowHandler 负责查找整个窗口内的物理事例
* EventWindow 定义整个窗口内物理事例的读取和写入的方式

### 4.窗口事例关联事例分析
EventAna可以作为多个Task，由于全局缓存中保存着每一个挑选后的索引数据所对应的一个窗口内的物
理事例，因此便可以对窗口内的事例数据进行多线程的关联事例分析。
* EventWinMemMgr类主要负责关联分析任务的内存管理
* WinInputSvc服务类，获取的、全局缓存中窗口数据
* WinOutputSvc服务类，全局缓存中窗口数据
* FullWinNavBuf服务类，提供窗口事例缓存服务
* BeginWinHdl 类处理从服务类WinInputSvc中获取的全局缓存中窗口数据，然后将整个窗口的数据加载到局部缓存FullWinNavBuf中
* BeginWinHdl 类处理关联数据分析之后的结果
* EventAnaAlg关联数据分析算法

### 5.处理关联分析的结果
EventWriter作为一个Task，处理关联分析之后的结果
* GBufPopAlg 算法，写入关联分析之后的结果

### 运行例子
source setup.sh  #source 环境
python Tag/run.py  #运行，输入是Index数据和文件路径列表，输出是挑选后的信号事例

## 总结
多线程处理Index数据，目前仍处于开发阶段。由于多个线程无法同时读取同一个Navigator，因此在从Index中读取事例数据和窗口内的事例数据时先将事例加载了一次，但是读取事例所占用的时间比例较大，因此多线程的结果并不是很明显。

因此在之后的研究中可以从两个方面提高关联事例分析的效率：
* 提出有效的解决方法，使得多个线程能够同时处理同一个Navigator
* 可以尝试直接将事例数据保存在内存中，多线程直接处理内存中的数据

### 附录
DataGen包中提供了产生OECEvent事例的方法
* DataGenRateAlg算法，用于按照本底事例率，产生具有时间顺序的本底事例（U238/Th232/K40）
* DataGenIBDAlg算法，用于按照IBD事例率，产生具有时间顺序的信号事例
* DataReadAlg算法，用于从OECEvent事例中产生txt格式的Index数据
