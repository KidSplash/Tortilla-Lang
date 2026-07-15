from Lexer import tokenize
import Semantic

code = '''
a = 2
array bob = [1, 3, 4]
if 2 is 3:
bob -= 3
end
func jumm() int {
    bob *= 2
    return 10
}
switch 2 <= 3:
case false:
also true:
bob = 10
end
jumm:[bob](jim, ted)
'''

"""

"""
tokens = tokenize(code)
tree = Semantic.Parse(tokens).parsePrgm()
treeNames = Semantic.hoist(tree)
nameChecker = Semantic.NameCheck(tree)
treeNames = nameChecker.walkNode(tree, treeNames, treeNames)