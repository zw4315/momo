DDD 标准分层

- Application（用例层）：编排事务、授权、调用领域与仓储，不含业务规则。
- Domain（领域层）：实体、值对象、领域服务、聚合根与仓储接口（Ports）。
- Infrastructure（基础设施）：仓储/网关/消息等“接口的实现”。
ref: fabiofumarola.github.io

idea:
- app 层就像一个不懂业务的总裁，懂的不是具体的业务实现，而是资源和流程的组合
