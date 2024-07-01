#### Prometheus

Prometheus 是一个数据监控的解决方案，为我们的系统提供指标收集和监控，让我们能随时掌握系统运行的状态，快速定位问题和排除故障。Prometheus 发展速度很快，使用go进行开发，12 年开发完成，16 年加入 CNCF，成为继 K8s 之后第二个 CNCF 托管的项目。

#### 整体生态

Prometheus 提供了从**指标暴露，到指标抓取、存储和可视化，以及最后的监控告警**等一系列组件。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvat3N2ReqCCVg7XYsr8ypHmC0cQ1PbOwFqGwczyibr5EFoXZCty2U0CgQaB9xTywuNG7833iaPk9ZliaA/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

##### 指标暴露

在prometheus中**每个被监控的服务都被称为job**，Prometheus 为这些 Job 提供了官方的 **SDK** ，利用这个 SDK 可以自定义并导出自己的业务指标，也可以使用 Prometheus 官方提供的各种常用组件和中间件的 **Exporter**（比如常用的 MySQL，Consul 等等）。**对于短时间执行的脚本任务或者不好直接 Pull 指标的服务，Prometheus 提供了 PushGateWay 网关给这些任务将服务指标主动推 Push 到网关，Prometheus 再从这个网关里 Pull 指标**。

##### 指标抓取

Prometheus中指标抓取有**Push**和**Pull**两种抓取模型。

1. Pull：**监控服务主动拉取被监控服务的指标。被监控服务一般通过主动暴露 metrics 端口或者通过 Exporter 的方式暴露指标，监控服务依赖服务发现模块发现被监控服务，从而去定期的抓取指标**。默认是一分钟拉取一次指标。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvat3N2ReqCCVg7XYsr8ypHmCnVjFACo0UTSNxK2gIJJRgC3BRfY7dpM0lUqghmmyibFfKWkgsZDrgAw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

2. Push：**被监控服务主动将指标推送到监控服务，可能需要对指标做协议适配，必须得符合监控服务要求的指标格式**。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvat3N2ReqCCVg7XYsr8ypHmCqjnYUgVwCxAvfibb5iafGEhNTBkCZod7VV8EYePfJyfVqQbCtwnuHFyQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

Prometheus 对外都是用的 Pull 模型，**一个是 Pull Exporter 的暴露的指标，一个是 Pull PushGateway 暴露的指标**。

##### 指标存储和查询

指标抓取后会**存储在内置的时序数据库中，Prometheus 也提供了 PromQL 查询语言给我们做指标的查询，我们可以在 Prometheus 的 WebUI 上通过 PromQL，可视化查询我们的指标，也可以很方便的接入第三方的可视化工具，例如 grafana**。

##### 监控告警

prometheus 提供了 **alertmanageer 基于 promql 来做系统的监控告警，当 promql 查询出来的指标超过我们定义的阈值时，prometheus 会发送一条告警信息到 alertmanager，manager 会将告警下发到配置好的邮箱**。

#### 工作原理

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvat3N2ReqCCVg7XYsr8ypHmCefe3d6ZZPc5j7WImNkV8ibR5LQhGstsSPJ3ibACwMtlFw2IXLFVZjvQA/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

##### 服务注册

首先明确2个概念：

1. job：被监控服务
2. target：被监控服务的单个实例

对于服务注册而言，就是在prometheus中对job和target进行注册。注册分为静态注册和动态注册。

**静态注册：静态的将服务的 IP 和抓取指标的端口号配置在 Prometheus yaml 文件的 scrape_configs 配置下:**

```
scrape_configs:
 - job_name: "prometheus"
   static_configs:
   - targets: ["localhost:9090"]
```

以上就是注册了一个名为 prometheus 的服务，这个服务下有一个实例，暴露的抓取地址是 localhost:9090。

**动态注册：动态注册就是在 Prometheus yaml 文件的 scrape_configs 配置下配置服务发现的地址和服务名，Prometheus 会去该地址，根据你提供的服务名动态发现实例列表，在 Prometheus 中，支持 consul，DNS，文件，K8s 等多种服务发现机制。**

基于 consul 的服务发现：

```
 - job_name: "node_export_consul"
  metrics_path: /node_metrics
  scheme: http
  consul_sd_configs:
   - server: localhost:8500
     services:
     - node_exporter
```

我们 consul 的地址就是：localhost:8500，服务名是 node_exporter，在这个服务下有一个 exporter 实例：localhost:9600。

> 我的理解简单来说，静态注册需要我们指定job和target的地址和端口；而动态注册只需要我们指定job的地址和端口，而具体的target实例的会通过发现机制去发现。

##### 配置更新

修改完Prometheus的配置后，需要进行配置更新加载。一种是通过重启，一种是通过动态更新。

第一步：首先要保证启动 Prometheus 的时候带上启动参数：--web.enable-lifecycle

```shell
prometheus --config.file=/usr/local/etc/prometheus.yml --web.enable-lifecycle
```

第二步：去更新我们的 Prometheus 配置:

第三步：**更新完配置后，我们可以通过 Post 请求的方式，动态更新配置**：

```shell
curl -v --request POST 'http://localhost:9090/-/reload'
```

原理：**Prometheus 在 web 模块中，注册了一个 handler**：

```go
if o.EnableLifecycle {
  router.Post("/-/quit", h.quit)
  router.Put("/-/quit", h.quit)
  router.Post("/-/reload", h.reload) // reload配置
  router.Put("/-/reload", h.reload)
}
```

**通过 h.reload 这个 handler 方法实现：这个 handler 就是往一个 channle 中发送一个信号**：

```go
func (h *Handler) reload(w http.ResponseWriter, r *http.Request) {
  rc := make(chan error)
  h.reloadCh <- rc  // 发送一个信号到channe了中
  if err := <-rc; err != nil {
   http.Error(w, fmt.Sprintf("failed to reload config: %s", err), http.StatusInternalServerError)
  }
}
```

**在 main 函数中会去监听这个 channel，只要有监听到信号，就会做配置的 reload，重新将新配置加载到内存中**：

```go
case rc := <-webHandler.Reload():
  if err := reloadConfig(cfg.configFile, cfg.enableExpandExternalLabels, cfg.tsdb.EnableExemplarStorage, logger, noStepSubqueryInterval, reloaders...); err != nil {
   level.Error(logger).Log("msg", "Error reloading config", "err", err)
   rc <- err
  } else {
   rc <- nil
  }
```

##### 指标抓取和存储

rometheus 对指标的抓取采取主动 Pull 的方式，即周期性的请求被监控服务暴露的 metrics 接口或者是 PushGateway，从而获取到 Metrics 指标，默认时间是 15s 抓取一次，配置项如下：

```
global:
 scrape_interval: 15s
```

**抓取到的指标会被以时间序列的形式保存在内存中，并且定时刷到磁盘上，默认是两个小时回刷一次。并且为了防止 Prometheus 发生崩溃或重启时能够恢复数据，Prometheus 也提供了类似 MySQL 中 binlog 一样的预写日志，当 Prometheus 崩溃重启时，会读这个预写日志来恢复数据**。

#### Metric

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvat3N2ReqCCVg7XYsr8ypHmC9UAL58GUia1v8T9FBAfL4DYAZDMy7L5dzx11g5tBSG4ABjFprzctfmw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

Prometheus **采集的所有指标都是以时间序列的形式进行存储**，每一个时间序列有三部分组成：

- **指标名和指标标签集合**：metric_name{<label1=v1>,<label2=v2>....}，
  - 指标名：表示这个指标是监控哪一方面的状态，比如 http_request_total 表示：请求数量；
  - 指标标签，描述这个指标有哪些维度，比如 http_request_total 这个指标，有请求状态码 code = 200/400/500，请求方式：method = get/post 等，实际上指标名称实际上是以标签的形式保存，这个标签是**name**，即：**name**=。
- **时间戳**：描述当前时间序列的时间，单位：毫秒。
- **样本值**：当前监控指标的具体数值，比如 http_request_total 的值就是请求数是多少。

#### Prometheus指标类型

Prometheus 底层存储上其实并没有对指标做类型的区分，都是以时间序列的形式存储，但是为了方便用户的使用和理解不同监控指标之间的差异，Prometheus 定义了 4 种不同的指标类型：**计数器 counter，仪表盘 gauge，直方图 histogram，摘要 summary**。

1. Counter 计数器：**Counter 类型和 redis 的自增命令一样，只增不减**，通过 Counter 指标可以统计 Http 请求数量，请求错误数，接口调用次数等单调递增的数据。同时可以结合 increase 和 rate 等函数统计变化速率，后续我们会提到这些内置函数。
2. Gauge 仪表盘：**和 Counter 不同，Gauge 是可增可减的，可以反映一些动态变化的数据**，例如当前内存占用，CPU 利用，Gc 次数等动态可上升可下降的数据，在 Prometheus 上通过 Gauge，可以不用经过内置函数直观的反映数据的变化情况。
3. Histogram 直方图：Histogram 是一种直方图类型，可以观察到指标在各个不同的区间范围的分布情况，如下图所示：可以观察到请求耗时在各个桶的分布。
4. **Summary 摘要**：Summary 也是用来做统计分析的，**和 Histogram 区别在于，Summary 直接存储的就是百分位数**，如下所示：可以直观的观察到样本的中位数，P90 和 P99。

#### Prometheus指标导出

指标导出有两种方式：

1. 一种是使用 **Prometheus 社区提供的定制好的 Exporter 对一些组件诸如 MySQL，Kafka** 等的指标作导出，
2. 也可以**利用社区提供的 Client 来自定义指标**导出。

自定义指标，大体流程为：

1. 定义指标（类型、名字、帮助信息）
2. 注册指标
3. 定义标签
4. 添加值

```go
package main

import (
  "fmt"
  "net/http"
  "github.com/prometheus/client_golang/prometheus"
)

var (
  MyCounter prometheus.Counter
)


// init 注册指标
func init() {
  // 1.定义指标（类型，名字，帮助信息）
  MyCounter = prometheus.NewCounter(prometheus.CounterOpts{
   Name: "my_counter_total",
   Help: "自定义counter",
  })

  // 2.注册指标
  prometheus.MustRegister(MyCounter)
}

// Sayhello
func Sayhello(w http.ResponseWriter, r *http.Request) {
  // 接口请求量递增
  MyCounter.Inc()
  fmt.Fprintf(w, "Hello Wrold!")
}
```

#### PromQL

通过prometheus提供的PromQL可以查询导出的指标，**PromQL 是 Prometheus 为我们提供的函数式的查询语言**，查询表达式有四种类型：

- **字符串**：只作为某些内置函数的参数出现
- **标量**：单一的数字值，可以是函数参数，也可以是函数的返回结果
- **瞬时向量**：某一时刻的时序数据。**直接通过指标名即可进行查询，查询结果是当前指标最新的时间序列，比如查询 Gc 累积消耗的时间，并设置指定标签进行过滤（也支持正则表达式）：go_gc_duration_seconds_count{instance="127.0.0.1:9600"}**
- **区间向量**：某一时间区间内的时序数据集合。**范围查询的结果集就是区间向量，可以通过[]指定时间来做范围查询，查询 5 分钟内的 Gc 累积消耗时间：go_gc_duration_seconds_count{}[5m]**

#### PromQL提供的常用内置函数

1. **rate 函数可以用来求指标的平均变化速率：rate函数=时间区间前后两个点的差 / 时间范围，一般 rate 函数可以用来求某个时间区间内的请求速率，也就是我们常说的 QPS**。
2. 但是 rate 函数只是算出来了某个时间区间内的平均速率，没办法反映突发变化，假设在一分钟的时间区间里，前 50 秒的请求量都是 0 到 10 左右，但是最后 10 秒的请求量暴增到 100 以上，这时候算出来的值可能无法很好的反映这个峰值变化。这个问题可以通过 irate 函数解决，i**rate 函数求出来的就是瞬时变化率：时间区间内最后两个样本点的差 / 最后两个样本点的时间差**。
3. **聚合函数：Sum() by() without()**：sum将指标值相加，by进行分组，without不通过xx分组

#### Grafana可视化

除了可以利用 Prometheus 提供的 webUI 可视化我们的指标外，还可以接入 Grafana 来做指标的可视化。

1. 对接数据源，配置Prometheus的地址
2. 创建仪表盘，编辑仪表盘，编写PromQL完成查询和可视化

#### 监控告警

**AlertManager 是 prometheus 提供的告警信息下发组件，包含了对告警信息的分组，下发，静默等策略。配置完成后可以在 webui 上看到对应的告警策略信息。告警规则也是基于 PromQL 进行定制的**。

在 prometheus.yml 中配置告警配置文件，需要配置上 alertmanager 的地址和告警文件的地址。配置告警信息，例如告警发送地址，告警内容模版，分组策略等都在 alertmanager 的配置文件中配置。