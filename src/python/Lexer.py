def tokenize(code):
    class token:
        def __init__(self, kind, val):
            self.kind = kind  #Kinds: Variable Name, Keyword, Operator, Int, Float, Bool, Str
            self.val = val  #Value or specifc type e.g. king = Operator, val = 'Plus'
            self.line = line  #Line Number
            self.col = col  #Column
    tokens = []
    code += " "  #Adds an ending space to the code so that the index does not go out of bounds
    mode = 0  #0 = Normal, 1 = Single-line Comment, 2 = Multi-line Comment, 3 = String
    line = 0
    col = 0
    qot = ''  #Quotation Type for Strings
    value = ''
    i = 0
    abc = 'asdfghjklqwertyuiopzxcvbnmASDFGHJKLQWERTYUIOPZXCVBNM_'

    keywords = [
        'is', 'not', 'in', 'has', 'xor', 'nor', 'and',
        'or', 'null', 'int', 'bigInt', 'float', 'doub',
        'char', 'str', 'bool', 'array', 'set', 'dict',
        'class', 'func', 'if', 'elif', 'else', 'switch',
        'case', 'default', 'for', 'while', 'forEach',
        'return', 'out', 'this', 'const', 'extends',
        'parent', 'type', 'label', 'goto', 'await',
        'async', 'pfor', 'try', 'soft', 'hard', 'catch',
        'also', 'end'
    ]
    singOps = {
        '+': 'Plus',
        '*': 'Times',
        '-': 'Minus',
        '/': 'Divide',
        '=': 'Assign',
        '%': 'Mod',
        '!': 'BitNot',
        '&': 'BitAnd',
        '^': 'BitXor',
        '|': 'BitOr',
        '(': 'Lpar',
        ')': 'Rpar',
        '[': 'Lbrc',
        ']': 'Rbrc',
        '<': 'Less',
        '>': 'More',
        '{': 'Lbrkt',
        '}': 'Rbrkt',
        ':': 'Then',
        '.': 'Point',
        ';': 'Semi',
        ',': 'Comma'
    }
    doubOps = {
        '++': 'Inc',
        '+=': 'PlusEql',
        '--': 'Dec',
        '-=': 'MinusEql',
        '**': 'Power',
        '*=': 'TimesEql',
        '/=': 'DivideEql',
        '%=': 'ModEql',
        '<=': 'Lte',
        '>=': 'Gte',
        '<<': 'Shl',
        '>>': 'Shr'
    }
    while i < len(code):
        #Increment line and column
        if code[i] == '\n':
            line += 1
            col = 0
        else:
            col += 1

        #Comment Removal
        if mode == 1 or mode == 2:
            if (i + 1 < len(code)) and [code[i], code[i + 1]] == ['#', '#']:
                i += 1
                mode = 0
            elif mode == 1 and code[i] == '\n':
                mode = 0
            i += 1
        #Normal Mode
        elif mode == 0:
            if code[i] in ' \n\t':
                i += 1
            elif code[i] == '#':
                i += 1
                if code[i] == '#':
                    mode = 2
                    i += 1
                else:
                    mode = 1
            #Checks for Number Literals
            elif code[i] in '0987654321':
                #If point becomes True, number is a float
                point = False
                num = code[i]
                i += 1
                while code[i] in '0987654321.':
                    num += code[i]
                    if code[i] == '.':
                        if point == True:
                            break
                        point = True
                    i += 1
                if point:
                    tokens.append(token('Float', num))
                else:
                    tokens.append(token('Int', num))
            #Starts a String
            elif code[i] == '`' or code[i] == '"' or code[i] == "'":
                mode = 3
                #Type of quote to look for
                qot = code[i]
                i += 1
            elif (code[i] + code[i + 1]) in doubOps:
                tokens.append(token("Operator", doubOps[code[i] + code[i + 1]]))
                i += 2
            elif code[i] in singOps:
                tokens.append(token("Operator", singOps[code[i]]))
                i += 1
            elif code[i] in abc:
                word = code[i]
                i += 1
                #Adds characters to the word until it finds a non number, letter, or underspace
                while code[i] in abc or code[i] in '0987654321':
                    word += code[i]
                    i += 1
                if word in keywords:
                    tokens.append(token('Keyword', word))
                elif word in ["true", 'false']:
                    tokens.append(token('Bool', word))
                else:
                    tokens.append(token('Variable', word))
        #String Mode
        elif mode == 3:
            #Repeats until it finds the correct end quote
            if code[i] == qot:
                tokens.append(token("Str", value))
                value = ""
                mode = 0
            else:
                value += code[i]
            i += 1

    return tokens
