/*

Foment

*/

#include "foment.hpp"
#include "unicode.hpp"

// ---- Characters ----

Define("char?", CharPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char?", argc);

    return(CharacterP(argv[0]) ? TrueObject : FalseObject);
}

Define("char=?", CharEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char=?", argc);
    CharacterArgCheck("char=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char=?", argv[adx]);

        if (AsCharacter(argv[adx - 1]) != AsCharacter(argv[adx]))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char<?", CharLessThanPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char<?", argc);
    CharacterArgCheck("char<?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char<?", argv[adx]);

        if (AsCharacter(argv[adx - 1]) >= AsCharacter(argv[adx]))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char>?", CharGreaterThanPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char>?", argc);
    CharacterArgCheck("char>?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char>?", argv[adx]);

        if (AsCharacter(argv[adx - 1]) <= AsCharacter(argv[adx]))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char<=?", CharLessThanEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char<=?", argc);
    CharacterArgCheck("char<=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char<=?", argv[adx]);

        if (AsCharacter(argv[adx - 1]) > AsCharacter(argv[adx]))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char>=?", CharGreaterThanEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char>=?", argc);
    CharacterArgCheck("char>=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char>=?", argv[adx]);

        if (AsCharacter(argv[adx - 1]) < AsCharacter(argv[adx]))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-ci=?", CharCiEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char-ci=?", argc);
    CharacterArgCheck("char-ci=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char-ci=?", argv[adx]);

        if (CharFoldcase(AsCharacter(argv[adx - 1])) != CharFoldcase(AsCharacter(argv[adx])))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-ci<?", CharCiLessThanPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char-ci<?", argc);
    CharacterArgCheck("char-ci<?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char-ci<?", argv[adx]);

        if (CharFoldcase(AsCharacter(argv[adx - 1])) >= CharFoldcase(AsCharacter(argv[adx])))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-ci>?", CharCiGreaterThanPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char-ci>?", argc);
    CharacterArgCheck("char-ci>?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char-ci>?", argv[adx]);

        if (CharFoldcase(AsCharacter(argv[adx - 1])) <= CharFoldcase(AsCharacter(argv[adx])))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-ci<=?", CharCiLessThanEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char-ci<=?", argc);
    CharacterArgCheck("char-ci<=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char-ci<=?", argv[adx]);

        if (CharFoldcase(AsCharacter(argv[adx - 1])) > CharFoldcase(AsCharacter(argv[adx])))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-ci>=?", CharCiGreaterThanEqualPPrimitive)(long_t argc, FObject argv[])
{
    AtLeastTwoArgsCheck("char-ci>=?", argc);
    CharacterArgCheck("char-ci>=?", argv[0]);

    for (long_t adx = 1; adx < argc; adx++)
    {
        CharacterArgCheck("char-ci>=?", argv[adx]);

        if (CharFoldcase(AsCharacter(argv[adx - 1])) < CharFoldcase(AsCharacter(argv[adx])))
            return(FalseObject);
    }

    return(TrueObject);
}

Define("char-alphabetic?", CharAlphabeticPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-alphabetic?", argc);
    CharacterArgCheck("char-alphabetic?", argv[0]);

    return(AlphabeticP(AsCharacter(argv[0])) ? TrueObject : FalseObject);
}

Define("char-numeric?", CharNumericPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-numeric?", argc);
    CharacterArgCheck("char-numeric?", argv[0]);

    return(DigitP(AsCharacter(argv[0])) ? TrueObject : FalseObject);
}

Define("char-whitespace?", CharWhitespacePPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-whitespace?", argc);
    CharacterArgCheck("char-whitespace?", argv[0]);

    return(WhitespaceP(AsCharacter(argv[0])) ? TrueObject : FalseObject);
}

Define("char-upper-case?", CharUpperCasePPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-upper-case?", argc);
    CharacterArgCheck("char-upper-case?", argv[0]);

    return(UppercaseP(AsCharacter(argv[0])) ? TrueObject : FalseObject);
}

Define("char-lower-case?", CharLowerCasePPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-lower-case?", argc);
    CharacterArgCheck("char-lower-case?", argv[0]);

    return(LowercaseP(AsCharacter(argv[0])) ? TrueObject : FalseObject);
}

Define("digit-value", DigitValuePrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("digit-value", argc);
    CharacterArgCheck("digit-value", argv[0]);

    long_t dv = DigitValue(AsCharacter(argv[0]));
    if (dv < 0 || dv > 9)
        return(FalseObject);
    return(MakeFixnum(dv));
}

Define("char->integer", CharToIntegerPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char->integer", argc);
    CharacterArgCheck("char->integer", argv[0]);

    return(MakeFixnum(AsCharacter(argv[0])));
}

Define("integer->char", IntegerToCharPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("integer->char", argc);
    FixnumArgCheck("integer->char", argv[0]);

    return(MakeCharacter(AsFixnum(argv[0])));
}

Define("char-upcase", CharUpcasePrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-upcase", argc);
    CharacterArgCheck("char-upcase", argv[0]);

    return(MakeCharacter(CharUpcase(AsCharacter(argv[0]))));
}

Define("char-downcase", CharDowncasePrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-downcase", argc);
    CharacterArgCheck("char-downcase", argv[0]);

    return(MakeCharacter(CharDowncase(AsCharacter(argv[0]))));
}

Define("char-foldcase", CharFoldcasePrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("char-foldcase", argc);
    CharacterArgCheck("char-foldcase", argv[0]);

    return(MakeCharacter(CharFoldcase(AsCharacter(argv[0]))));
}

static FObject Primitives[] =
{
    CharPPrimitive,
    CharEqualPPrimitive,
    CharLessThanPPrimitive,
    CharGreaterThanPPrimitive,
    CharLessThanEqualPPrimitive,
    CharGreaterThanEqualPPrimitive,
    CharCiEqualPPrimitive,
    CharCiLessThanPPrimitive,
    CharCiGreaterThanPPrimitive,
    CharCiLessThanEqualPPrimitive,
    CharCiGreaterThanEqualPPrimitive,
    CharAlphabeticPPrimitive,
    CharNumericPPrimitive,
    CharWhitespacePPrimitive,
    CharUpperCasePPrimitive,
    CharLowerCasePPrimitive,
    DigitValuePrimitive,
    CharToIntegerPrimitive,
    IntegerToCharPrimitive,
    CharUpcasePrimitive,
    CharDowncasePrimitive,
    CharFoldcasePrimitive
};

void SetupCharacters()
{
    for (ulong_t idx = 0; idx < sizeof(Primitives) / sizeof(FPrimitive *); idx++)
        DefinePrimitive(Bedrock, BedrockLibrary, Primitives[idx]);
}
