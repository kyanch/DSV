# Geometry 
平台无关的几何形状存储类，依赖glm做坐标变换

AABB(AxisAlignedBoundingBox) 和 Point 为底层数据，被Geometry及其派生依赖

假定坐标轴
```text
    0 ----------------------> X axis
    |
    |
    |
    |         *(x,y)
    |
    |
    |
    V
  Y axis

```
