// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/bigquery/v2/minimal/internal/project_connection.h"
#include "google/cloud/bigquery/v2/minimal/internal/project_options.h"
#include "google/cloud/bigquery/v2/minimal/internal/project_rest_connection_impl.h"
#include "google/cloud/bigquery/v2/minimal/internal/project_rest_stub_factory.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include <memory>

namespace google {
namespace cloud {
namespace bigquery_v2_minimal_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ProjectConnection::~ProjectConnection() = default;

StreamRange<Project> ProjectConnection::ListProjects(
    ListProjectsRequest const&) {
  return google::cloud::internal::MakeStreamRange<Project>(
      []() -> absl::variant<Status, Project> {
        return Status(StatusCode::kUnimplemented, "not implemented");
      });
}

std::shared_ptr<ProjectConnection> MakeProjectConnection(Options options) {
  internal::CheckExpectedOptions<CommonOptionList, UnifiedCredentialsOptionList,
                                 ProjectPolicyOptionList>(options, __func__);
  options = ProjectDefaultOptions(std::move(options));

  auto project_rest_stub = CreateDefaultProjectRestStub(options);

  return std::make_shared<ProjectRestConnectionImpl>(
      std::move(project_rest_stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery_v2_minimal_internal
}  // namespace cloud
}  // namespace google
