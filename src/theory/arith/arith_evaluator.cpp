/******************************************************************************
 * Top contributors (to current version):
 *   Gereon Kremer
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2022 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * Arithmetic evaluator.
 */
#include "theory/arith/arith_evaluator.h"

#include "theory/arith/nl/poly_conversion.h"
#include "theory/rewriter.h"
#include "theory/theory.h"
#include "util/real_algebraic_number.h"

namespace cvc5::internal {
namespace theory {
namespace arith {

std::optional<bool> isExpressionZero(Env& env,
                                     Node expr,
                                     const std::vector<TNode>& nodes,
                                     const std::vector<TNode>& repls)
{
  // Substitute constants and rewrite
  expr = env.getRewriter()->rewrite(expr);
  if (expr.isConst())
  {
    return expr.getConst<Rational>().isZero();
  }
  expr =
      expr.substitute(nodes.begin(), nodes.end(), repls.begin(), repls.end());
  expr = env.getRewriter()->rewrite(expr);
  if (expr.isConst())
  {
    return expr.getConst<Rational>().isZero();
  }
  if (expr.getKind() == Kind::REAL_ALGEBRAIC_NUMBER)
  {
    return isZero(expr.getOperator().getConst<RealAlgebraicNumber>());
  }
  return std::nullopt;
}

}  // namespace arith
}  // namespace theory
}  // namespace cvc5::internal
