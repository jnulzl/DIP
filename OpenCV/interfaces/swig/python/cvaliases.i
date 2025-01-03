%module cv
%pythoncode %{
IPL_ALIGN_DWORD=IPL_ALIGN_4BYTES
IPL_ALIGN_QWORD=IPL_ALIGN_8BYTES
CV_MAKE_TYPE=CV_MAKETYPE
CV_IS_CONT_MAT=CV_IS_MAT_CONT
CV_HIST_TREE=CV_HIST_SPARSE
CV_TERMCRIT_NUMBER=CV_TERMCRIT_ITER
CV_SEQ_ELTYPE_PTR=CV_USRTYPE1
CV_GRAPH=CV_SEQ_KIND_GRAPH
CV_SEQ_CONTOUR=CV_SEQ_POLYGON
CV_STORAGE_WRITE_TEXT=CV_STORAGE_WRITE
CV_STORAGE_WRITE_BINARY=CV_STORAGE_WRITE
CV_NODE_INTEGER=CV_NODE_INT
CV_NODE_FLOAT=CV_NODE_REAL
CV_NODE_STRING=CV_NODE_STR
cvGetSubArr=cvGetSubRect
cvZero=cvSetZero
cvCvtScale=cvConvertScale
cvScale=cvConvertScale
cvCvtScaleAbs=cvConvertScaleAbs
cvCheckArray=cvCheckArr
cvMatMulAddEx=cvGEMM
cvMatMulAddS=cvTransform
cvT=cvTranspose
cvMirror=cvFlip
cvInv=cvInvert
cvMahalonobis=cvMahalanobis
CV_DXT_INVERSE_SCALE=CV_DXT_INV_SCALE
cvFFT=cvDFT
cvGraphFindEdge=cvFindGraphEdge
cvGraphFindEdgeByPtr=cvFindGraphEdgeByPtr
cvDrawRect=cvRectangle
cvDrawLine=cvLine
cvDrawCircle=cvCircle
cvDrawEllipse=cvEllipse
cvDrawPolyLine=cvPolyLine
CV_FONT_VECTOR0=CV_FONT_HERSHEY_SIMPLEX
CV_RGB2RGBA=CV_BGR2BGRA
CV_RGBA2RGB=CV_BGRA2BGR
CV_RGB2BGRA=CV_BGR2RGBA
CV_BGRA2RGB=CV_RGBA2BGR
CV_RGB2BGR=CV_BGR2RGB
CV_RGBA2BGRA=CV_BGRA2RGBA
CV_GRAY2RGB=CV_GRAY2BGR
CV_GRAY2RGBA=CV_GRAY2BGRA
CV_BayerBG2RGB=CV_BayerRG2BGR
CV_BayerGB2RGB=CV_BayerGR2BGR
CV_BayerRG2RGB=CV_BayerBG2BGR
CV_BayerGR2RGB=CV_BayerGB2BGR
%}
