# 3D-no-martices
Basic 3D Graphics without matrices

**Look mum no matrices!**

Comments:

- made from scratch
- no matrix needed! :-)
- needs optimization
- it is not a 3D engine!
- code needs tidy up 
- have a look a the 4D cube (Tesseract) rotating

Technical commments:

- Perlin noise 
    for a random smoth movement of each shape.
- world, local space
    every shape has a local 3D-space and each of these space are a child of the global space
    (wold space) or of another local space.
- linked list
    as the shapes are moving, they can get in or out of the camera view. Just those shapes
    that are in the view of the camera are drawn. The criterion to determine which shapes
    are in or out of the camnera view is the cosine of the angle between the centroid of 
    the shape and the view of the camera (Z-axis), the threshold for this is set based on
    the focal distance and the projection plane dimensions. We could sort the array of shapes
    base on this criterion, however we use two linked lists with vector support (relLink class).
         

Video [here](http://46.32.229.68/img/3d.html)

![Example](http://46.32.229.68/img/3d.png)


