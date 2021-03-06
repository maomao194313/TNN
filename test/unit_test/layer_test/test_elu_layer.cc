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

#include "test/unit_test/layer_test/layer_test.h"
#include "test/unit_test/unit_test_common.h"
#include "test/unit_test/utils/network_helpers.h"
#include "tnn/utils/dims_utils.h"

namespace TNN_NS {

class EluLayerTest : public LayerTest,
                     public ::testing::WithParamInterface<std::tuple<int, int, int, int, float, DataType>> {};

INSTANTIATE_TEST_SUITE_P(LayerTest, EluLayerTest,
                         ::testing::Combine(
                             // batch
                             testing::Values(1, 2),
                             // channel Values(1, 8),
                             testing::Values(1, 4, 15),
                             // size Values(16, 19),
                             testing::Values(1, 6, 8, 13),
                             // dim count
                             testing::Values(2, 3, 4, 5),
                             // alpha
                             testing::Values(-1.234, 2.30, 0.564),
                             // data_type
                             testing::Values(DATA_TYPE_FLOAT)));

TEST_P(EluLayerTest, EluLayer) {
    // get param
    int batch          = std::get<0>(GetParam());
    int channel        = std::get<1>(GetParam());
    int input_size     = std::get<2>(GetParam());
    int dim_count      = std::get<3>(GetParam());
    float alpha        = std::get<4>(GetParam());
    DataType data_type = std::get<5>(GetParam());
    DeviceType dev     = ConvertDeviceType(FLAGS_dt);

    if(CheckDataTypeSkip(data_type)) {
        GTEST_SKIP();
    }

    if (DEVICE_OPENCL == dev && dim_count > 4) {
        GTEST_SKIP();
    }

    // param
    std::shared_ptr<EluLayerParam> param(new EluLayerParam());
    param->name  = "Elu";
    param->alpha = alpha;

    // generate interpreter
    std::vector<int> input_dims = {batch, channel};
    while(input_dims.size() < dim_count) input_dims.push_back(input_size);
    auto interpreter            = GenerateInterpreter("Elu", {input_dims}, param);
    Run(interpreter);
}

}  // namespace TNN_NS
