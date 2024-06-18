## 什么是Git

Git是一个**分布式版本控制系统，跟踪目录里的修改。它的工作流是非线性的**（不同电脑上的平行分支形成了一个graph）。和主从式的系统不一样的是，每台电脑上的每个git目录都是一个完整的repo，包含全部历史和完整的版本跟踪能力。

关于工作流是非线性的，这意味着它支持多种并行开发路径，并能够处理复杂的分支和合并操作。建立分支、rebase、修订commit、强制推送、cherry-pick、分支复位，在git都是很正常的使用方式。

关于合并和rebase：这两种操作都是用来整合来自不同分支的改动。合并操作会保留分支的历史，而**rebase则是将一系列的提交“移植”到另一个分支的新基点上，这有助于创建一个更线性的历史**。

## 什么不是Git

### GitHub/GitLab

只是提供Git服务的社区和网站，Git本身并不需要网络。

### Fork

### Pull Request/Merge Request

Code Review和合并的流程。

## 分支策略

Git的工作流是基于分支的。**不但每个repo是平等的，每个分支也是。Master/main、develop这些只是为了简化管理而人工指定的有特殊含义的分支**。这里的分支策略是为了更好地协作而产生的习惯规范，不是git的工作流本身必须定义的。分支可以分为几个层次。

### main

整个项目的稳定分支，里面的内容可能相对较老，但是这个分支里的内容都是经过测试和验证的。原先都叫master，因为政治正确的要求，最近越来越多新项目开始用main。有些快速开发的项目甚至不采用main分支。

### Develop

开发主要发生在develop分支。新特性先放到这个分支，再去优化和增强稳定性。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAUg9mYicxz4T1FW7ZemRFB6OIZQSg2HvPnsWPa5F3ib3mB3wQ1hAqeia4Q/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

对于跨团队的大项目，每个团队都有自己的兴趣点和发布周期。**很常见的做法是，每个团队有自己的develop分支。每过一段时间合并到总的develop分支。一般来说，中等大小的团队，专注于repo的某一部分，可以采取这样的分支形式。小团队或者个人没有必要有自己的develop分支。那样反而会浪费时间和增加合并过程中的风险**。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAsMP7sV1Tz0kmFaxMpib1I8driaia17K4omwNnVHtxB5y7qYQJLaUrxnYA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

### Feature

Feature分支是生命期很短的分支，专注于单个特性的开发。

- 从develop分支上新建一个feature分支
- 提交一些关于这个feature的代码
- 合并回去
- 删除这个feature分支

对于本地repo里的feature分支，你可以做任何事。常见的用法是在开发过程中非常频繁地提交，走一小步就提交一次。在发出MR之前，先合并成一个commit，把这个分支变整洁，方便后续操作。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAsqBnPpHwibl3LHEkka9mqs9feVzOqv9cVxUYUHwjJTT4TpZxkLg2J5Q/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

### Release分支群

就好像一个目录，包含了不同版本给不同产品线的release分支。

## Merge还是Rebase

**Merge**

把一个分支合并到目标分支，在顶上建立一个commit用来合并，两个分支里已有的commit不会有变化。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_gif/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAJ9p8rNt8ajWkzEKtAT2icNUT8cVicKPUqUCXLMA6NLHqrAPj1pgnzfRQ/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

**Rebase**

从分支分出来的地方切开，嫁接到目标分支的顶端上。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_gif/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAkwTUQ4Wa7NxIFHnxobD12TBrISDg9LX2VePFKuiaZWkxD5fXsKNrCJQ/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

**squash**

选择一个分支里的一些commit，压扁成一个commit。

<img src="https://mmbiz.qpic.cn/sz_mmbiz_gif/j3gficicyOvavGakaVxzVI9nT1Yk61A8tAH9zTC0TZcF9DoUh7gkt21qwWouutlOEVk3EeSj3vCficIsRqxIoUibxw/640?wx_fmt=gif&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

**对于Feature分支，最好是使用Rebase和Squash**：

历史简洁性：通过使用 squash 将一个 feature 分支的多个 commits 压缩成一个单一的 commit，可以使主分支的历史更加清晰和易于管理。这样做的结果是，每个 feature 都对应一个单独的 commit，使得历史线性化，便于理解和回溯。

避免无意义的合并 commit：使用 rebase 而不是 merge 来将 feature 分支整合到 develop 或 main 分支可以避免产生那些“合并 commit”，这些 commit 在功能上通常没有实际内容，只是表明了一个合并行为。

减少冲突解决的复杂性：在合并之前进行 rebase，可以先解决与基底分支的冲突，这使得合并操作更为简单，因为 rebase 会将 feature 分支的起点移动到目标分支的最新提交上。


