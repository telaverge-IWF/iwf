/*********************************-*CPP*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/

#include "Rules.h"
#include "Component.h"
namespace eAccelero
{

// TODO String exceptions to proper exceptions
// Deletion of pointers on exception

// TODO don't have to really include all the tokens, probably till regex will do
OpFunctor OpFunctorAccess::m_fptrTable[Lexer::TOK_MAX] = {
    NULL, NULL, NULL, NULL,         // 0 - 3
    &OperandValBase::And,           // 4
    &OperandValBase::Or,            // 5
    &OperandValBase::LesserEqual,   // 6
    &OperandValBase::Lesser,        // 7    
    &OperandValBase::EqualTo,       // 8
    &OperandValBase::NotEqual,      // 9
    &OperandValBase::GreaterEqual,  // 10
    &OperandValBase::Greater,       // 11
    NULL, NULL, NULL,               // 12 - 14
    &OperandValBase::Match,         // 15
    NULL, NULL                      // 16, 17
};


OperandValBase* LocalVarOperand::GetVal(RuleRuntime *runTime)
{
    return runTime->GetOperandVal(((IntVal*)m_val)->Get());
}


Rule::Rule(const char *name, uint16_t ruleId, uint16_t priority, void* data)
  : m_ruleId(ruleId),
    m_priority(priority),
    //m_atoms(RULE_MAX_ATOM),
    m_name(name),
    m_ruleData(data)
{
}

Rule::~Rule()
{
    for (RuleAtomList::iterator it = m_atoms.begin(); it != m_atoms.end();)
    {
        delete *it;
        it = m_atoms.erase(it);
    }

}

bool Rule::Evaluate(RuleRuntime *rt)
{
    int sz = m_atoms.size();
    int i = 0;
    bool res;
    RuleAtom *cur = NULL;

    // allocating the memory on stack makes it much faster than new and delete
    char p[1024];
    rt->PushRuleStack((void*)p, sz);

    while (i < sz)
    {
        cur = m_atoms[i];
        res = cur->Evaluate(rt);
        rt->SetResult(i, res);
        if (res && cur->OrPassJump() != RuleAtom::RuleInvalidJump)
        {
            i = cur->OrPassJump();
            rt->SetResult(i, 1); // set the result of this to Pass
        }
        else if (!res && cur->AndFailJump() != RuleAtom::RuleInvalidJump)
        {
            i = cur->AndFailJump();
            rt->SetResult(i, 0); // Set the result as fail
        }
        i++;
    }

    res = rt->GetResult(sz-1);

    rt->PopRuleStack();

    return res;
}

RuleTable::RuleTable()
{
}

RuleTable::~RuleTable()
{
    this->Flush();
    for (VarHandlerTable::iterator it = m_varHandlerTable.begin();
            it != m_varHandlerTable.end(); )
    {
        //delete it->second;
        m_varHandlerTable.erase(it++);
    }
}

void RuleTable::Flush()
{
    ScopedWriteLock lock(m_rulesLock);
    for (RulesMap::iterator it = m_rules.begin(); it != m_rules.end();)
    {
        delete it->second;
        m_rules.erase(it++);
    }
}

void RuleTable::AddRule(const char* name, uint16_t ruleId,
                    uint16_t priority, ExprRef &expr, void *data)
{
    ScopedWriteLock lock(m_rulesLock);
    unsigned key = ruleId | (priority << 16);

    RulesMap::iterator it = m_rules.find(key);
    if (it != m_rules.end())
    {
        throw RuleException("Duplicate rule added");
    }
    Rule *rule = new Rule(name, ruleId, priority, data);

    ConstructPostFix(rule, expr);

    m_rules[key] = rule;
}

int RuleTable::ConstructPostFix(Rule *rule, ExprRef &expr)
{
    if (IsComparison(expr->m_op))
    {
        Operand* lhs = ConstructOperand(expr->m_lhs);
        Operand* rhs = ConstructOperand(expr->m_rhs);
        return rule->AddAtom(lhs, rhs, expr->m_op);
    }

    int retLhs = ConstructPostFix(rule, expr->m_lhs);
    int retRhs = ConstructPostFix(rule, expr->m_rhs);

    int ret = rule->AddAtom(rule->GetAtomAt(retLhs),
                         rule->GetAtomAt(retRhs), expr->m_op);

    if (expr->m_op == Lexer::TOK_AND)
    {
        // if the LHS expr fails, then it can jump to current
        rule->GetAtomAt(retLhs)->AndFailJump(ret);
    }
    else if (expr->m_op == Lexer::TOK_OR)
    {
        // if the LHS is sucess, don't have to evaluate RHS
        rule->GetAtomAt(retLhs)->OrPassJump(ret);
    }

    return ret;
}

Operand* RuleTable::ConstructOperand(ExprRef &term)
{
    Operand* op = NULL;
    std::string tokStr = term->m_token->m_token;
    switch(term->m_type)
    {
        case Expr::TypeInt:
        {
            int val = atoi(tokStr.c_str()); // Handle hex
            op = new Operand(new IntVal(val), Expr::TypeInt);
            break;
        }
        case Expr::TypeString:
        {
            op = new Operand(new StringVal(tokStr), Expr::TypeString);
            break;
        }
        case Expr::TypeRegex:
        {
            op = new Operand(new RegexVal(tokStr.c_str()), Expr::TypeRegex);
            break;
        }
        case Expr::TypeVar:
        {
            size_t idx = tokStr.find_first_of('.');
            if (idx != std::string::npos)
            {
                VarIdentifier id;
                memset(&id, 0, sizeof(id));

                id.varType = VarTypeUserDefined;
                std::string str = tokStr.substr(0, idx);

                VarHandlerTable::iterator it = m_varHandlerTable.find(str);
                if (it == m_varHandlerTable.end())
                {
                    throw RuleException("No valid operand constructor found");
                }
                op = it->second->ConstructOperand(tokStr, id);
            }
            else
            {
                // TODO Handle for runtime variable
                std::stringstream ss;
                ss << "Variable '" << tokStr << "' not defined";
                throw RuleException(ss.str().c_str());
            }
            break;
        }
        default:
            throw RuleException("Operand not handled!");
    }
    return op;
}

bool RuleTable::Match(RuleRuntime *rt, RuleMatch& singleMatch)
{
    ScopedReadLock lock(m_rulesLock);
    bool matched = false;

    for (RulesMap::iterator it = m_rules.begin(); it != m_rules.end(); it++)
    {
        rt->CurrentRule(it->second);
        if (it->second->Evaluate(rt))
        {
            singleMatch.ruleName = it->second->Name();
            singleMatch.userData = it->second->GetData();
            matched = true;
            break;
        }
    }
    return matched;
}

int RuleTable::Match(RuleRuntime *rt, std::vector<RuleMatch>& multiMatch)
{
    ScopedReadLock lock(m_rulesLock);
    int count = 0;
    RuleMatch match;

    for (RulesMap::iterator it = m_rules.begin(); it != m_rules.end(); it++)
    {
        rt->CurrentRule(it->second);
        if (it->second->Evaluate(rt))
        {
            count++;
            match.ruleName = it->second->Name();
            match.userData = it->second->GetData();
            multiMatch.push_back(match);
        }
    }
    return count;
}


} // namespace eAccelero
