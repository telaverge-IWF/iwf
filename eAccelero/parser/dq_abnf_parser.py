#!/usr/bin/python

import re
import copy

# Recursive desent parser
# ABNF grammer parser RFC 5234
#
# Terminals, Literals (Regular expressions)
# Operators
#   Concatenation       Rule1 Rule2
#   Alternatives        Rule1 | Rule2
#   Sequence Group      (Rule1 Rule2)
#   Variable Repetition <min>*<max>Rule
#   Specific Repetition <num>Rule
#   Optional sequence   [Rule1]
#   Comment              ; some text

class ParserException(Exception):
    def __init__(self, loc, parse_str, err_str = ''):
        self.lineno = parse_str.count("\n", 0, loc) + 1
        self.col = loc - parse_str.rfind("\n", 0, loc)
        self.err_str = err_str

    def __str__(self):
        return 'Parse Error: Line %d %d - %s' % (self.lineno, self.col, self.err_str)
       
def skipWhiteSpaces(loc, parse_str):
    str_len = len(parse_str)
    while loc < str_len and parse_str[loc] in " \t\n\r":
        loc += 1
    return loc

OP_NONE = 0
OP_AND  = 1
OP_OR   = 2
OP_DICT = {0 : 'OP_NONE', 1 : 'OP_AND', 2 : 'OP_OR'}

class Rule(object):
    def __init__(self, rule1, rule2, operator):
        self.name = None
        self.parse_action = None
        self.rules = [rule1, rule2]
        self.operator = operator

    def setName(self, rule_name):
        self.name = rule_name

    def setParseAction(self, parse_action):
        self.parse_action = parse_action

    def parseString(self, parse_str):
        parsed_tokens = []
        try:
            loc = self.parse(parse_str, 0, parsed_tokens)
        except AttributeError:
            print parsed_tokens
            raise
        return parsed_tokens

    def parse(self, parse_str, loc = 0, parsed_tokens = None):
        if self.operator == OP_AND:
            loc = self.doConcat(loc, parse_str, parsed_tokens)
        elif self.operator == OP_OR:
            loc = self.doAlternate(loc, parse_str, parsed_tokens)
        return loc

    def doConcat(self, loc, parse_str, parsed_tokens):
        loc = self.rules[0].parse(parse_str, loc, parsed_tokens)
        if self.rules[1] == None:
            print loc
            print self.printTree()
            assert self.rules[1]
        loc = self.rules[1].parse(parse_str, loc, parsed_tokens)
        return loc 

    def doAlternate(self, loc, parse_str, parsed_tokens):
        tokens = None
        for rule in self.rules:
            try:
                loc = rule.parse(parse_str, loc, parsed_tokens)
                return loc
            except ParserException as e:
                #if not isinstance(rule, Rule):
                #    print rule.term_str, loc, parse_str
                pass
        raise ParserException(loc, parse_str, 'No match for AND operation')

    def __add__(self, rhs_rule):
        #print 'Rule: add'
        return Rule(self, rhs_rule, OP_AND)

    def __or__(self, rhs_rule):
        #print 'Rule: or'
        return Rule(self, rhs_rule, OP_OR)

    def __ior__(self, lhs):
        assert self.operator == OP_OR
        assert len(self.rules) >= 2
        assert self.rules[1] != None
        self.rules.append(lhs)
        return self

    def printTree(self, level = 0):
        name = self.name
        if name == None: name = ''
        ret_str = '  ' * level + '%s %s %s' % (self.__class__, name, OP_DICT[self.operator])
        level += 1
        for rule in self.rules:
            if rule == None: continue
            ret_str += '\n'
            ret_str += rule.printTree(level)
        return ret_str



class Terminal(object):
    def __init__(self, term_str, term_name = None, parse_action = None, suppress = False, skip_white_space = True):
        self.term_str = term_str
        self.parse_action = parse_action
        self.name = term_name
        self.suppress = suppress
        self.skip_ws = skip_white_space

    def setName(self, name):
        self.name = name

    def preParse(self, loc, parse_str):
        if self.skip_ws:
            loc = skipWhiteSpaces(loc, parse_str)
        return loc

    def parse(self, parse_str, loc = 0, parsed_tokens = None):
        loc = self.preParse(loc, parse_str)
        loc, token = self.parseImpl(loc, parse_str)
        token = self.postParse(loc, token)
        if self.name:
            token = {self.name: token}
        if parsed_tokens != None and not self.suppress:
            parsed_tokens.append(token)
        return loc

    def postParse(self, loc, token):
        val = token
        if self.parse_action: 
            val = self.parse_action(token)
        return val

    def copy(self):
        return copy.copy(self)

    def __add__(self, rhs_term):
        #print 'Terminal: add'
        return Rule(self, rhs_term, OP_AND)

    def __or__(self, rhs_term):
        #print 'Terminal: or'
        return Rule(self, rhs_term, OP_OR)

    def printTree(self, level = 0):
        name = self.name
        if name == None: name = ''
        return '  ' * level + '%s %s' % (self.__class__, name)

class Literal(Terminal):
    def __init__(self, term_str, term_name = None, parse_action = None, suppress = False, skip_white_space = True):
        super(Literal, self).__init__(term_str, term_name, parse_action, suppress, skip_white_space)
        self.term_len = len(term_str)

    def parseImpl(self, loc, parse_str):
#        print loc, parse_str 
        if not parse_str.startswith(self.term_str, loc):
            raise ParserException(loc, parse_str, 'Literal not matched')
        loc += self.term_len
        return loc, self.term_str

class Not(Terminal):
    def __init__(self, term_str, term_name = None, parse_action = None, suppress = False, skip_white_space = True):
        super(Not, self).__init__(term_str, term_name, parse_action, suppress, skip_white_space)
        self.term_len = len(term_str)

    def parseImpl(self, loc, parse_str):
#        print loc, parse_str
        eloc = parse_str.find(self.term_str, loc)
        if eloc == -1:
            raise ParserException(loc, parse_str, '%s not matched' % self.term_str)
        return eloc, parse_str[loc:eloc]

class Regex(Terminal):
    def __init__(self, term_str, term_name = None, parse_action = None, suppress = False, skip_white_space = True):
        super(Regex, self).__init__(term_str, term_name, parse_action, suppress, skip_white_space)
        self.re = re.compile(self.term_str)

    def parseImpl(self, loc, parse_str):
        match = self.re.match(parse_str, loc)
        if not match:
            raise ParserException(loc, parse_str, 'Regex %s not matched' % self.term_str)
        loc = match.end()
        return loc, match.group()

class Group(Rule):
    def __init__(self, rule, name = None):
        super(Group, self).__init__(rule, None, OP_NONE)
        self.name = name

    def parse(self, parse_str, loc, parsed_tokens):
        group_tokens = []
        loc = self.rules[0].parse(parse_str, loc, group_tokens)
        if self.name:
            parsed_tokens.append({self.name: group_tokens})
        else:
            parsed_tokens.append(group_tokens)
        return loc

class Repeat(Rule):
    def __init__(self, rule, mini = 0, maxi = 1024, name = None, parse_action = None):
        super(Repeat, self).__init__(rule, None, OP_NONE)
        self.name = name
        self.mini = mini
        self.maxi = maxi
        self.parse_action = parse_action

    def parse(self, parse_str, loc, parsed_tokens):
        repeat_tokens = []
        repeat_count = 0
        while repeat_count < self.maxi:
            try:
                loc = self.rules[0].parse(parse_str, loc, repeat_tokens)
                repeat_count += 1
            except ParserException as e:
                if repeat_count < self.mini:
                    raise ParserException(loc, parse_str, 'Repeat: minimum condition not met')
                break
        if self.parse_action: repeat_tokens = self.parse_action(repeat_tokens)
        if repeat_tokens != None:
            if isinstance(repeat_tokens, list) and not len(repeat_tokens):
                return loc
            if self.name:
                parsed_tokens.append({self.name: repeat_tokens})
            else:
                parsed_tokens.append(repeat_tokens)
        return loc

# Helpers
#

def oneOf(term_list, name = None):
    assert len(term_list) > 2
    one_of_rule = Literal(term_list[0], name) | Literal(term_list[1], name)
    for term in term_list[2:]:
        one_of_rule |= Literal(term, name)
    return one_of_rule

def oneOfRules(rule_list, name = None):
    assert len(rule_list) > 2
    one_of_rule = rule_list[0]
    start = 1
    if not isinstance(rule_list[0], Rule):
        one_of_rule = rule_list[0] | rule_list[1]
        start = 2
    for rule in rule_list[start:]:
        one_of_rule |= rule
    return one_of_rule

def suppress(term_str, skip_ws = True):
    return Literal(term_str, suppress = True, skip_white_space = skip_ws)

class LineComment(Regex):
    def __init__(self, comment_chars):
        term_str = r'[%s][^\n]*' % comment_chars
        super(LineComment, self).__init__(term_str, None, None, True)

class LineCommentCplusType(Regex):
    def __init__(self,comment_chars):
        term_str = r'%s[^\n]*' % comment_chars
        super(LineCommentCplusType, self).__init__(term_str, None, None, True)

class Optional(Repeat):
    def __init__(self, rule, default_val = None):
        super(Optional, self).__init__(rule, 0, 1, None, parse_action = self.parseAction)
        self.default_val = default_val

    def parseAction(self, token):
        if len(token) == 0:
            return self.default_val
        if len(token) == 1:
            return token[0]
        return token

_toInt = lambda token: int(token)
def number(token_name = None):
    return Regex(r'\d+', term_name = token_name, parse_action = _toInt)

string_end = Regex(r'$', suppress = True)
line_end = Regex(r'[ \t]*(\n|$)', suppress = True, skip_white_space = False)

if __name__ == '__main__':
    """
    lit = Literal('Hello World!', 'test_token')
    parsed_tokens = []
    loc = lit.parse('Hello World! How are you?', 0, parsed_tokens)
    print loc, parsed_tokens

    lit = Literal('Hello World!')
    parsed_tokens = []
    loc = lit.parse('Hello World! How are you?', 0, parsed_tokens)
    print loc, parsed_tokens

    try:
        lit = Literal('Hello World!')
        parsed_tokens = []
        loc = lit.parse('How are you? Hello World! How are you?', 0, parsed_tokens)
        print loc, parsed_tokens
    except ParserException as e:
        print e

    reg = Regex(r'\d+')
    parsed_tokens = []
    s = 'Roll no: 22'
    loc = reg.parse(s, 8, parsed_tokens)
    print loc, parsed_tokens

    reg = Regex(r'[a-zA-Z0-9][a-zA-Z0-9-]*')
    loc = reg.parse('3gpp-release4: 22', 0, parsed_tokens)
    print loc, parsed_tokens
    rule = Regex(r'[a-zA-Z0-9][a-zA-Z0-9-]*', 'rhs') +\
           Literal('::=', suppress = True) + Regex(r'\d+', 'lhs')
    #parsed_tokens = rule.parseString('3gpp-release9 ::= 1234')
    #print parsed_tokens 

    rule1 = (Literal('Hello', 'h') | Literal('World', 'w') ) + rule
    #parsed_tokens = rule1.parseString('World 3gpp-release9 ::= 1234')
    #print parsed_tokens 

    print '-' * 40
    rule2 = Group(rule1, 'group1') + Group(rule, 'group2')
    parsed_tokens = rule2.parseString("World 3gpp-release9 ::= 1234\nsome-rule::=8976")
    print parsed_tokens
    #"""

    comment = LineComment('#;')

    rule = Regex(r'[a-zA-Z0-9][a-zA-Z0-9-]*', 'command_name') +\
           Literal('::=', suppress = True) +\
           Repeat(  comment | (Literal('[', suppress = True) +\
                          Regex(r'[a-zA-Z0-9][a-zA-Z0-9-]*') +\
                          Literal(']', suppress = True) ), name = 'avps' ) +\
           string_end
    dia_gram = """
Test-Command ::= [avp1]
                 [avp2]
                 ; this is a comment
                 [avp3]
                 # [does not match]
                 [avp4]

"""
    tokens = rule.parseString(dia_gram)
    print tokens

    test_rule = Literal("show command") + Optional( Literal("object") ) +\
                Optional( Literal("instance") ) + Literal("test") + string_end
    tokens = test_rule.parseString("show command object test")
    print tokens
    tokens = test_rule.parseString("show command object instance test")
    print tokens
    tokens = test_rule.parseString("show command test")
    print tokens

    one_of_rule = Literal("I'll drink", suppress = True) +\
                  oneOf(['tea', 'coffee', 'coke', 'water'], name = 'drink') +\
                  string_end
    match_strs = ["I'll drink tea", "I'll drink coffee", "I'll drink water"]
    for match_str in match_strs:
        tokens = one_of_rule.parseString(match_str)
        print tokens

    line_str = """
!dict 2567"""
    line_parse = suppress('!dict') + number('num') + line_end
    tokens = line_parse.parseString(line_str)
    print tokens

    print '=' * 80
    tstr = '''
    before
      %{ 
    this is a sample string
    having multi line values
    watever matches is gotten
    %}
    after
    %{ 
    CAPS MATCH
    %}
    end
    '''
    plain = ''
    def GetPlain(tokens):
        global plain
        plain += tokens
        return None
    mrule = suppress('%{') + Not('%}', parse_action=GetPlain, suppress=True) + suppress('%}')
    bef = Literal('before');
    af  = Literal('after')
    en  = Literal('end')
    trule = Repeat( oneOfRules([bef, af, en, mrule]) )
    tokens = trule.parseString(tstr)
    print tokens
    print plain
