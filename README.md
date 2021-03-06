[中文版本](README_CH.md)
<div align=left ><img src="https://gitee.com/darren3d/tnn-resource/raw/master/TNN.png"/>

## Introduction

TNN: A high-performance, lightweight neural network inference framework open sourced by Tencent Youtu Lab. It also has many outstanding advantages such as cross-platform, high performance, model compression, and code tailoring. The TNN framework further strengthens the support and performance optimization of mobile devices on the basis of the original Rapidnet and ncnn frameworks. At the same time, it refers to the high performance and good scalability characteristics of the industry's mainstream open source frameworks, and expands the support for X86 and NV GPUs. On the mobile phone, TNN has been used by many applications such as mobile QQ, weishi, and Pitu. As a basic acceleration framework for Tencent Cloud AI, TNN has provided acceleration support for the implementation of many businesses. Everyone is welcome to participate in the collaborative construction to promote the further improvement of the TNN reasoning framework.

## Effect Example

<table>
    <tr>
        <th nowrap="nowrap">Face Detection(blazeface)</th>
        <th nowrap="nowrap">Object Detection(yolov5s)</th>
        <th nowrap="nowrap">Face Alignment<br>(from Tencent Youtu Lab)</th>
    </tr>
    <tr>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/blazeface><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/face_detection.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/blazeface>model link</a>
        </td>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/yolov5><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/object-detection.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/yolov5>model link</a>
        </td>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/youtu_face_alignment><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/face_alignment.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/youtu_face_alignment>model link</a>
        </td>
    </tr>
    <tr>
        <th nowrap="nowrap">Hair Segmentation<br>(from Tencent Guangying Lab)</th>
        <th nowrap="nowrap">Pose Estimation<br>(from Tencent Guangliu)</th>
        <th nowrap="nowrap">Pose Estimation(blazepose)</th>
    </tr>
    <tr>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/hair_segmentation><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/hair_seg_red.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/hair_segmentation>model link</a>
        </td>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/skeleton><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/skeleton_guangliu.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/skeleton>model link</a>
        </td>
        <td>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/blazepose><img src=https://raw.githubusercontent.com/darrenyao87/tnn-models/master/doc/demo/skeleton_blazepose.gif height=320></src> </a> <br>
            <a href=https://github.com/darrenyao87/tnn-models/tree/master/model/blazepose>model link</a>
        </td>
    </tr>
</table>

## Quick Start

It is very simple to use TNN. If you have a trained model, the model can be deployed on the target platform through three steps.
1. Convert the trained model into a TNN model. We provide a wealth of tools to help you complete this step, whether you are using Tensorflow, Pytorch, or Caffe, you can easily complete the conversion.
Detailed hands-on tutorials can be found here [How to Create a TNN Model](doc/en/user/convert_en.md).

2. When you have finished converting the model, the second step is to compile the TNN engine of the target platform. You can choose among different acceleration solutions such as ARM/OpenCL/Metal/NPU/X86/CUDA according to the hardware support.
   For these platforms, TNN provides convenient one-click scripts to compile. For detailed steps, please refer to [How to Compile TNN](doc/en/user/compile_en.md).

3. The final step is to use the compiled TNN engine for inference. You can make program calls to TNN inside your application. We provide a rich and detailed demo as a reference to help you complete.
    * [Run an iOS Demo](doc/en/user/demo_en.md)
    * [Run an Android Demo](doc/en/user/demo_en.md)
    * [Run an Linux/Windows Demo](doc/en/user/demo_en.md)

## Technical Solutions

At present, TNN has been launched in various major businesses, and its following characteristics have been widely praised.

* Computation optimization
    * The backend operators are primely optimized to make the best use of computing power in different architectures, regarding instruction issue, throughput, delay, cache bandwidth, cache delay, registers, etc..
    * The TNN performance on mainstream hardware platforms (CPU: ARMv7, ARMv8， X86, GPU: Mali, Adreno, Apple， NV GPU， NPU) has been greatly tuned and improved.
    * The convolution function is implemented by various algorithms such as Winograd, Tile-GEMM, Direct Conv, etc., to ensure efficiency under different parameters and sizes.
    * Op fusion: TNN can do offline analysis of network graph, fuse multiple simple operations and reduce overhead such as redundant memory access and kernel startup cost.

* Low precision computation acceleration
    * TNN supports INT8/FP16 mode, reduces model size & memory consumption, and utilizes specific hardware low-precision instructions to accelerate calculations.
    * TNN supports INT8 WINOGRAD algorithm, (input 6bit), further reduces the model calculation complexity without sacrificing the accuracy.
    * TNN supports mixed-precision data in one model, speeding up the model's calculation speed while preserving its accuracy.

* Memory optimization
    * Efficient "memory pool" implementation: Based on a full network DAG analysis, the implementation reuses memory between non-dependent nodes which reduces memory cost by 90%.
    * Cross-model memory reduces: This supports external real-time design for network memory so that multiple models can share mutual memory.

* The performance of mainstream models on TNN: v0.1 2020.05.29

    * Kirin970：

        | model                     | cpu time(single thread, ms) | gpu time(ms) | 
        |---------------------------|--------------|--------------| 
        | Mobilenet_v1              | 88           |   12         | 
        | Mobilenet_v1_int8         | 55           |              | 
        | Mobilenet_v2              | 58           |   11         | 
        | Mobilenet_v2_int8         | 41           |              | 
        | squeezenet_v1.0           | 127          |   20         | 
        | squeezenet_v1.0_int8      | 82           |              | 

    * Snapdragon 835：

        | model                     | cpu time(single thread, ms) | gpu time(ms) |
        |---------------------------|--------------|--------------|
        | Mobilenet_v1              | 94           |   16         |
        | Mobilenet_v1_int8         | 62           |              |
        | Mobilenet_v2              | 61           |   14         |
        | Mobilenet_v2_int8         | 47           |              |
        | squeezenet_v1.0           | 122          |   28         |
        | squeezenet_v1.0_int8      | 93           |              |

    * Snapdragon 845：

        | model                     | cpu time(single thread, ms) | gpu time(ms) |
        |---------------------------|--------------|--------------|
        | Mobilenet_v1              | 60           |   10         |
        | Mobilenet_v1_int8         | 37           |              |
        | Mobilenet_v2              | 39           |   8          |
        | Mobilenet_v2_int8         | 28           |              |
        | squeezenet_v1.0           | 74           |   14         |
        | squeezenet_v1.0_int8      | 56           |              |


* TNN architecture diagram：

   <div><img src="https://gitee.com/darren3d/tnn-resource/raw/master/doc/en/imgs/tnn_architect.jpg"/>

* TNN supports TensorFlow, Pytorch, MxNet, Caffe, and other training frameworks through ONNX, leveraging the continuous improvement of the ONNX open-source society.
  Currently, TNN supports 100+ ONNX operators, consisting of most of the mainstream CNN, NLP operators needed.
* TNN runs on mainstream operating systems (Android, iOS, embedded Linux, Windows, Linux), and is compatible with ARM CPU,X86 GPU, NPU hardware platform.
* TNN is constructed through Modular Design, which abstracts and isolates components such as model analysis, graph construction, graph optimization, low-level hardware adaptation, and high-performance kernel.
   It uses "Factory Mode" to register and build devices, that tries to minimize the cost of supporting more hardware and acceleration solutions.
* The size of the mobile dynamic library is only around 400KB, and it provides basic image conversion operations, which are light-weight and convenient. TNN uses unified models and interfaces across platforms and can switch easily by configuring just one single parameter.

## Learn About TNN Abilities
* [Operator Support](doc/en/user/support_en.md)
* [Model Support](doc/en/user/support_en.md)
* [Device Support](doc/en/user/support_en.md)
* [Profiling](doc/en/development/profiling_en.md)

## Manual
* [Compile TNN](doc/en/user/compile_en.md)
* [Tools]()
    * [Create a TNN Model](doc/en/user/convert_en.md)
    * [Model Quantization](doc/en/user/quantization_en.md)
    * [Model Visualization Netron](https://lutzroeder.github.io/netron/)
    * [Performance Analysis](doc/en/development/profiling_en.md)
    * [Model Alignment](doc/en/development/model_check_en.md)

## API Document
* [API call](doc/en/user/api_en.md)

## Contribute to TNN
* [Development Basics](doc/en/development/contributing_en.md)
* [Detailed Architecture](doc/en/development/architecture_en.md)
* [Add a New Operator](doc/en/development/add_op_en.md)
* [Unit Test](doc/en/development/unit_test_en.md)

## Roadmap
* [Road map](doc/cn/user/roadmap.md)

## Acknowledgement
TNN referenced the following projects：

* [ncnn](https://github.com/Tencent/ncnn)

* [mace](https://github.com/XiaoMi/mace.git)

* [MNN](https://github.com/alibaba/MNN)

* [caffe-onnx](https://github.com/htshinichi/caffe-onnx)

* [tensorflow-onnx](https://github.com/onnx/tensorflow-onnx)

* [onnx](https://github.com/onnx/onnx)

* [onnxruntime](https://github.com/microsoft/onnxruntime)

* [openvino](https://github.com/openvinotoolkit/openvino)

## License
* [BSD 3 Clause](LICENSE)

## FAQ
* [FAQ](doc/en/faq_en.md)

## Join Us

* Everyone is welcome to participate to build the best inference framework in the industry.

* Technical Discussion QQ Group: 913940506 Answer: TNN

* Scan the QR code to join the TNN discussion group：
<div align=left ><img src="https://gitee.com/darren3d/tnn-resource/raw/master/TNN-QQ.png"/>
