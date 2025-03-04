// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// FieldMask related utility methods.

#ifndef GOOGLE_PROTOBUF_UTIL_INTERNAL_FIELD_MASK_UTILITY_H__
#define GOOGLE_PROTOBUF_UTIL_INTERNAL_FIELD_MASK_UTILITY_H__

#include <functional>
#include <stack>

#include <google/protobuf/stubs/callback.h>
#include <google/protobuf/stubs/common.h>
#include "absl/status/status.h"
#include "absl/strings/string_view.h"


namespace google {
namespace protobuf {
namespace util {
namespace converter {

typedef std::function<std::string(absl::string_view)> ConverterCallback;
typedef std::function<absl::Status(absl::string_view)> PathSinkCallback;

// Applies a 'converter' to each segment of a FieldMask path and returns the
// result. Quoted strings in the 'path' are copied to the output as-is without
// converting their content. Escaping is supported within quoted strings.
// For example, "ab\"_c" will be returned as "ab\"_c" without any changes.
std::string ConvertFieldMaskPath(const absl::string_view path,
                                 ConverterCallback converter);

// Decodes a compact list of FieldMasks. For example, "a.b,a.c.d,a.c.e" will be
// decoded into a list of field paths - "a.b", "a.c.d", "a.c.e". And the results
// will be sent to 'path_sink', i.e. 'path_sink' will be called once per
// resulting path.
// Note that we also support Apiary style FieldMask form. The above example in
// the Apiary style will look like "a.b,a.c(d,e)".
absl::Status DecodeCompactFieldMaskPaths(absl::string_view paths,
                                         PathSinkCallback path_sink);

}  // namespace converter
}  // namespace util
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_UTIL_INTERNAL_FIELD_MASK_UTILITY_H__
