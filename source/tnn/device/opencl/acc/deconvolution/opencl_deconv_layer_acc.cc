// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tnn/device/opencl/acc/deconvolution/opencl_deconv_layer_common_acc.h"
#include "tnn/device/opencl/acc/deconvolution/opencl_deconv_layer_depthwise_acc.h"
#include "tnn/device/opencl/acc/opencl_layer_acc.h"
#include "tnn/device/opencl/imagebuffer_convertor.h"

namespace TNN_NS {

class OpenCLDeconvLayerAcc : public OpenCLLayerAcc {
public:
    virtual Status Init(Context *context, LayerParam *param, LayerResource *resource, const std::vector<Blob *> &inputs,
                        const std::vector<Blob *> &outputs) override;

    virtual ~OpenCLDeconvLayerAcc() override;

    virtual Status Reshape(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) override;

    virtual Status Forward(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) override;

private:
    std::shared_ptr<OpenCLLayerAcc> deconv_acc_implement_ = nullptr;
};

Status OpenCLDeconvLayerAcc::Init(Context *context, LayerParam *param, LayerResource *resource,
                                  const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    ConvLayerParam *conv_param = dynamic_cast<ConvLayerParam *>(param);

    if (OpenCLDeconvLayerDepthwiseAcc::IsPrefered(conv_param, inputs, outputs)) {
        deconv_acc_implement_ = std::make_shared<OpenCLDeconvLayerDepthwiseAcc>();
    } else if (OpenCLDeconvLayerCommonAcc::IsPrefered(conv_param, inputs, outputs)) {
        deconv_acc_implement_ = std::make_shared<OpenCLDeconvLayerCommonAcc>();
    }

    if (deconv_acc_implement_ == nullptr)
        return Status(TNNERR_OPENCL_ACC_INIT_ERROR, "this type deconv is not implemented");

    return deconv_acc_implement_->Init(context, conv_param, resource, inputs, outputs);
}

OpenCLDeconvLayerAcc::~OpenCLDeconvLayerAcc() {}

Status OpenCLDeconvLayerAcc::Reshape(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    Status ret = OpenCLLayerAcc::Reshape(inputs, outputs);
    CHECK_TNN_OK(ret)

    if (deconv_acc_implement_ == nullptr)
        return Status(TNNERR_OPENCL_ACC_RESHAPE_ERROR, "this type deconv is not implemented");

    return deconv_acc_implement_->Reshape(inputs, outputs);
}

Status OpenCLDeconvLayerAcc::Forward(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    if (deconv_acc_implement_ == nullptr)
        return Status(TNNERR_OPENCL_ACC_FORWARD_ERROR, "this type deconv is not implemented");

    return deconv_acc_implement_->Forward(inputs, outputs);
}

REGISTER_OPENCL_ACC(Deconv, LAYER_DECONVOLUTION)
REGISTER_OPENCL_LAYOUT(LAYER_DECONVOLUTION, DATA_FORMAT_NHC4W4);

}  // namespace TNN_NS
