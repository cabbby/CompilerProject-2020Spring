/*
 * MIT License
 * 
 * Copyright (c) 2020 Size Zheng

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include "RHSDecompVisitor.h"

namespace Boost {

namespace Internal {


void RHSDecompVisitor::visit(Ref<const IntImm> op) {
    res.push_back(make_pair((Expr)op, sgn));
}


void RHSDecompVisitor::visit(Ref<const UIntImm> op) {
    res.push_back(make_pair((Expr)op, sgn));
}


void RHSDecompVisitor::visit(Ref<const FloatImm> op) {
    res.push_back(make_pair((Expr)op, sgn));
}


void RHSDecompVisitor::visit(Ref<const StringImm> op) {
    res.push_back(make_pair((Expr)op, sgn));
}


void RHSDecompVisitor::visit(Ref<const Unary> op) {
    (op->a).visit_expr(this);
}

void RHSDecompVisitor::visit(Ref<const Binary> op) {
    if ((op->op_type == BinaryOpType::Add || op->op_type == BinaryOpType::Sub) && !op->bracketed) {
        sgn = 1;
        (op->a).visit_expr(this);
        if (op->op_type == BinaryOpType::Sub)
            sgn = -1;
        (op->b).visit_expr(this);
        sgn = 1;
    } else {
        res.push_back(make_pair((Expr)op, sgn));
    }
}


void RHSDecompVisitor::visit(Ref<const Compare> op) {
}


void RHSDecompVisitor::visit(Ref<const Select> op) {
}


void RHSDecompVisitor::visit(Ref<const Call> op) {
}


void RHSDecompVisitor::visit(Ref<const Cast> op) {
}


void RHSDecompVisitor::visit(Ref<const Ramp> op) {
}


void RHSDecompVisitor::visit(Ref<const Var> op) {
    res.push_back(make_pair((Expr)op, sgn));
}


void RHSDecompVisitor::visit(Ref<const Dom> op) {
}


void RHSDecompVisitor::visit(Ref<const Index> op) {
}


void RHSDecompVisitor::visit(Ref<const LoopNest> op) {
}


void RHSDecompVisitor::visit(Ref<const IfThenElse> op) {
}


void RHSDecompVisitor::visit(Ref<const Move> op) {
}


void RHSDecompVisitor::visit(Ref<const Kernel> op) {
}

void RHSDecompVisitor::visit(Ref<const StmtList> op) {
}

void RHSDecompVisitor::visit(Ref<const VarDeclaration> op) {
}


}  // namespace Internal

}  // namespace Boost
