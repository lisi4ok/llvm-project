//===-- BreakpointBase.h ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_TOOLS_LLDB_DAP_BREAKPOINTBASE_H
#define LLDB_TOOLS_LLDB_DAP_BREAKPOINTBASE_H

#include "DAPForward.h"
#include <string>

namespace lldb_dap {

struct BreakpointBase {
  // Associated DAP session.
  DAP &dap;

  // An optional expression for conditional breakpoints.
  std::string condition;
  // An optional expression that controls how many hits of the breakpoint are
  // ignored. The backend is expected to interpret the expression as needed
  std::string hitCondition;

  explicit BreakpointBase(DAP &d) : dap(d) {}
  BreakpointBase(DAP &d, const llvm::json::Object &obj);
  virtual ~BreakpointBase() = default;

  virtual void SetCondition() = 0;
  virtual void SetHitCondition() = 0;
  virtual void CreateJsonObject(llvm::json::Object &object) = 0;

  void UpdateBreakpoint(const BreakpointBase &request_bp);

  static const char *GetBreakpointLabel();
};

} // namespace lldb_dap

#endif
