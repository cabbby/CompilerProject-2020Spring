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

#include "BoundInferenceVisitor.h"

namespace Boost {

namespace Internal {


void BoundInferenceVisitor::visit(Ref<const IntImm> op) {
}


void BoundInferenceVisitor::visit(Ref<const UIntImm> op) {
}


void BoundInferenceVisitor::visit(Ref<const FloatImm> op) {
}


void BoundInferenceVisitor::visit(Ref<const StringImm> op) {
}


void BoundInferenceVisitor::visit(Ref<const Unary> op) {
}

void BoundInferenceVisitor::visit(Ref<const Binary> op) {
    int _lo = lo, _hi = hi;
    if (op->op_type == BinaryOpType::Add) { 
        if ((op->b).node_type() == IRNodeType::IntImm) {
            IntImm* e = (IntImm*) ((op->b).get());
            lo -= e->value(), hi -= e->value();
            (op->a).visit_expr(this);
        } else {
            (op->a).visit_expr(this);
            lo = _lo, hi = _hi;
            (op->b).visit_expr(this);
        }
    } else if (op->op_type == BinaryOpType::Mul) {
        IntImm* e = (IntImm*) ((op->b).get());
        lo = ceil((double)lo / e->value()), hi = ceil((double)hi / e->value());
        (op->a).visit_expr(this);
    } else if (op->op_type == BinaryOpType::IDiv) {
        IntImm* e = (IntImm*) ((op->b).get());
        lo *= e->value(), hi *= e->value();
        (op->a).visit_expr(this);
    }
}


void BoundInferenceVisitor::visit(Ref<const Compare> op) {
}


void BoundInferenceVisitor::visit(Ref<const Select> op) {
}


void BoundInferenceVisitor::visit(Ref<const Call> op) {
}


void BoundInferenceVisitor::visit(Ref<const Cast> op) {
}


void BoundInferenceVisitor::visit(Ref<const Ramp> op) {
}


void BoundInferenceVisitor::visit(Ref<const Var> op) {

}


void BoundInferenceVisitor::visit(Ref<const Dom> op) {
}


void BoundInferenceVisitor::visit(Ref<const Index> op) {
    if (mp.find(op->name) == mp.end())
        mp[op->name] = make_pair(0, 1 << 30);
    mp[op->name].first = max(mp[op->name].first, lo);
    mp[op->name].second = min(mp[op->name].second, hi);
}


void BoundInferenceVisitor::visit(Ref<const LoopNest> op) {
}


void BoundInferenceVisitor::visit(Ref<const IfThenElse> op) {
}


void BoundInferenceVisitor::visit(Ref<const Move> op) {
}


void BoundInferenceVisitor::visit(Ref<const Kernel> op) {
}

void BoundInferenceVisitor::visit(Ref<const StmtList> op) {
}

void BoundInferenceVisitor::visit(Ref<const VarDeclaration> op) {
}

}  // namespace Internal

}  // namespace Boost
