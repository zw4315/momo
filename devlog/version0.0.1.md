## Vertion 0.0.1

- 对于用户输入 parser，
- 对于用户输入 parser，
- 对于用户输入 parser，
- 对于用户输入 parser，如果 view 不带参数，则
- 对于用户输入 parser，如果是 view 一个日期，则认为是 查看这个日期和今日之间的任务
- 作为用户，为了拥有持续保存数据，输入应该被数据库记录下来，可以查看验证
- 作为用户，为了对事件的数量和时间维度有认知，在输入给定截止日期时，打印相关的时间图和事件列表
- As model, in order to respond to user query, it should have the ability to provide a collection of events
- As model, in order to be provided for searching, the structure should have id and name
- As model, in order to be classified coreectly, it should have multiple labels
- As model, in order to get the accumulated effects, each model should have various certain quantities
- As model, in order to provide 'View' with all relavent events, it should support a data stru for list of events
- As view，为了对事件有整体局部的看法，得有左右两个分屏
- As view, in order to hightlight specific days, rendering function should be aware of a list of special days
- 作为 parser，需要有 a 这个 enum，来做数据库的记录
- 作为 parser，为了解析事件，需要校验事件名 + （自动分配id）+ opt 截止时间 + opt 分类的 tag
- 作为 parser，为了自动正确分类事件，需要把输入事件和已有的 tags 做匹配

- 要有系统调用，知道今日是哪一天
- 要能对特定日子做反差色处理
- 背后需要有数据库，可以先 sqlite 

## Control

- 支持输入日期，给出对应日历和事件列表
-

## Todo

-[] 查看 todosim 里面的用户数据库交互的部分
-[] 文档里补充单例模式的设计

## History

2025.08.06 - 2025-0810
- doing 写 IT 检测 db 储存用户输入
- doing 把输入改成表驱动的形式
- 添加第一个 utils 的测试用例，跑通第一个用例

2025.08.02
- 支持输入两个日期，显示 days remains

2025.07.31
- 安装 clang-format 做原始文件的 codestyle 改进
