#include "LLVMGen.h"
#include <unordered_map>

/*
define: %# = alloca DT, align #
store: store DT Value, ptr %#, align #
operation: %# = load DT, ptr %#, align #
return: ret DT %#
*/



int varNames = 0;
std::string metaStart = "define i32 @main() #0 {\n";
std::string metaEnd = "}";
std::string define = "";
std::string store = "";
std::string change = "";
std::string ret = "ret i32 ";

std::unordered_map<DataType, std::string> DTtoStr{
    {DataType::None, ""},
    {DataType::Null, ""},
    {DataType::Int, "i32"},
    {DataType::Bigint, "i64"},
    {DataType::Float, "float"},
    {DataType::Doub, "double"},
    {DataType::Bool, "i1"},
    {DataType::Char, "i8"},
};
std::unordered_map<DataType, char> DTtoAlign{
        {DataType::None, '1'},
        {DataType::Null, '1'},
        {DataType::Int, '4'},
        {DataType::Bigint, '8'},
        {DataType::Float, '4'},
        {DataType::Doub, '8'},
        {DataType::Bool, '1'},
        {DataType::Char, '4'},
    };

void subfunt(subType type, std::string text, DataType DT, std::string too, std::string text2) {
    switch (type) {
        case(subType::alloca):
            too.append("%" + text + " = alloca " + DTtoStr[DT] + ", align " + DTtoAlign[DT] + "\n");
            break;
        case(subType::load):
            too.append("%" + std::to_string(varNames) + " = load " + DTtoStr[DT] + ", ptr %" + text + ", align " + DTtoAlign[DT] + "\n");
            ++varNames;
            break;
        case(subType::store):
            too.append("store " + DTtoStr[DT] + " %" + text + ", ptr %" + text2 + ", align " + DTtoAlign[DT] + "\n");
            break;
        case(subType::BitXor):
        case(subType::Xor):
            too.append("%" + std::to_string(varNames) + " = xor " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            break;
        case(subType::BitOr):
        case(subType::Or):
            too.append("%" + std::to_string(varNames) + " = or " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            break;
        case(subType::BitAnd):
        case(subType::And):
            too.append("%" + std::to_string(varNames) + " = and " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            break;
        case(subType::BitNot):
        case(subType::Not):
            too.append("%" + std::to_string(varNames) + " = xor " + DTtoStr[DT] + ", %" + text + ", -1\n");
            break;
        case(subType::Plus):
            if (DT == DataType::Int or DT == DataType::Bigint) {
                too.append("%" + std::to_string(varNames) + " = add " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            else {
                too.append("%" + std::to_string(varNames) + " = fadd " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            break;
        case(subType::Minus):
            if (DT == DataType::Int or DT == DataType::Bigint) {
                too.append("%" + std::to_string(varNames) + " = sub " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            else {
                too.append("%" + std::to_string(varNames) + " = fsub " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            break;
        case(subType::Times):
            if (DT == DataType::Int or DT == DataType::Bigint) {
                too.append("%" + std::to_string(varNames) + " = mul " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            else {
                too.append("%" + std::to_string(varNames) + " = fmul " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            break;
        case(subType::Divide):
            if (DT == DataType::Int or DT == DataType::Bigint) {
                too.append("%" + std::to_string(varNames) + " = sdiv " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            else {
                too.append("%" + std::to_string(varNames) + " = fdiv " + DTtoStr[DT] + ", %" + text + ", %" + text2 + "\n");
            }
            break;
        case(subType::Modulo):
            too.append();
            break;
        default:
    }
}


/*
Sub-Functions:
Negative
Plus
Minus
Times
Divide
Modulo
Power
Less
More
Gte
Lte
Is
*/

/*
%2 = alloca i32, align 4  //int a
%3 = alloca float, align 4 //float b
%4 = alloca double, align 8 //double c
%6 = alloca i32, align 4 //int e
store i32 10, ptr %2, align 4 //a = 10
store float 0x4028333340000000, ptr %3, align 4 //b = 12.1
store double 1.501000e+01, ptr %4, align 8 //c = 15.01
store i32 2, ptr %6, align 4 //e = 2
%7 = load i32, ptr %2, align 4 //a =
%8 = sitofp i32 %7 to float //e > float
%9 = load float, ptr %3, align 4 //b =
%10 = fadd float %8, %9 //a + b
%11 = fptosi float %10 to i32 //(a + b) > int
store i32 %11, ptr %6, align 4 //e = (a + b)
%12 = load i32, ptr %6, align 4 //e =
%13 = add nsw i32 %12, 2 //e + 2
store i32 %13, ptr %6, align 4 //e = (e + 2)
%14 = load i32, ptr %2, align 4 //a =
%15 = load i32, ptr %6, align 4 //e =
%16 = add nsw i32 12, %15 //e + 12
%17 = mul nsw i32 %14, %16 //a * (e + 12)
ret i32 %17*/ //return (a * (e + 12))