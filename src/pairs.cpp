/*

Foment

*/

#include "foment.hpp"

// ---- Pairs ----

FObject MakePair(FObject first, FObject rest)
{
    FPair * pair = (FPair *) MakeObject(PairTag, sizeof(FPair), 2, "cons");
    pair->First = first;
    pair->Rest = rest;

    return(pair);
}

void WritePair(FWriteContext * wctx, FObject obj)
{
    wctx->WriteCh('(');
    for (;;)
    {
        wctx->Write(First(obj));
        if (PairP(Rest(obj)))
        {
            wctx->WriteCh(' ');
            obj = Rest(obj);
        }
        else if (Rest(obj) == EmptyListObject)
        {
            wctx->WriteCh(')');
            break;
        }
        else
        {
            wctx->WriteStringC(" . ");
            wctx->Write(Rest(obj));
            wctx->WriteCh(')');
            break;
        }
    }
}

typedef enum
{
    ProperList,
    DottedList,
    CircularList
} FListType;

static FListType ListType(FObject lst)
{
    FObject fst = lst;
    FObject slw = lst;

    for (;;)
    {
        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(DottedList);

        fst = Rest(fst);
        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(DottedList);
        if (fst == slw)
            return(CircularList);

        fst = Rest(fst);
        FAssert(PairP(slw));
        slw = Rest(slw);

        if (fst == slw)
            return(CircularList);
    }

    return(ProperList);
}

static long_t ListLengthPlus(FObject lst)
{
    long_t ll = 0;
    FObject fst = lst;
    FObject slw = lst;

    for (;;)
    {
        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(ll);

        fst = Rest(fst);
        ll += 1;

        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(ll);
        if (fst == slw)
            return(-1);

        fst = Rest(fst);
        ll += 1;

        FAssert(PairP(slw));
        slw = Rest(slw);

        if (fst == slw)
            return(-1);
    }

    return(ll);
}

long_t ListLength(FObject lst)
{
    long_t ll = 0;
    FObject fst = lst;
    FObject slw = lst;

    for (;;)
    {
        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(-1);

        fst = Rest(fst);
        ll += 1;

        if (fst == EmptyListObject)
            break;

        if (PairP(fst) == 0)
            return(-1);
        if (fst == slw)
            return(-1);

        fst = Rest(fst);
        ll += 1;

        FAssert(PairP(slw));
        slw = Rest(slw);

        if (fst == slw)
            return(-1);
    }

    return(ll);
}

long_t ListLength(const char * nam, FObject lst)
{
    long_t ll = ListLength(lst);
    if (ll < 0)
        RaiseExceptionC(Assertion, nam, "expected a list", List(lst));

    return(ll);
}

FObject ReverseListModify(FObject list)
{
    FObject rlist = EmptyListObject;

    while (list != EmptyListObject)
    {
        FAssert(PairP(list));

        FObject obj = list;
        list = Rest(list);
//        AsPair(obj)->Rest = rlist;
        SetRest(obj, rlist);
        rlist = obj;
    }

    return(rlist);
}

FObject List(FObject obj)
{
    return(MakePair(obj, EmptyListObject));
}

FObject List(FObject obj1, FObject obj2)
{
    return(MakePair(obj1, MakePair(obj2, EmptyListObject)));
}

FObject List(FObject obj1, FObject obj2, FObject obj3)
{
    return(MakePair(obj1, MakePair(obj2, MakePair(obj3, EmptyListObject))));
}

FObject List(FObject obj1, FObject obj2, FObject obj3, FObject obj4)
{
    return(MakePair(obj1, MakePair(obj2, MakePair(obj3, MakePair(obj4, EmptyListObject)))));
}

FObject List(FObject obj1, FObject obj2, FObject obj3, FObject obj4, FObject obj5)
{
    return(MakePair(obj1, MakePair(obj2, MakePair(obj3, MakePair(obj4,
            MakePair(obj5, EmptyListObject))))));
}

FObject List(FObject obj1, FObject obj2, FObject obj3, FObject obj4, FObject obj5,
    FObject obj6)
{
    return(MakePair(obj1, MakePair(obj2, MakePair(obj3, MakePair(obj4,
            MakePair(obj5, MakePair(obj6, EmptyListObject)))))));
}

FObject List(FObject obj1, FObject obj2, FObject obj3, FObject obj4, FObject obj5,
    FObject obj6, FObject obj7)
{
    return(MakePair(obj1, MakePair(obj2, MakePair(obj3, MakePair(obj4,
            MakePair(obj5, MakePair(obj6, MakePair(obj7, EmptyListObject))))))));
}

Define("pair?", PairPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("pair?", argc);

    return(PairP(argv[0]) ? TrueObject : FalseObject);
}

Define("cons", ConsPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("cons", argc);

    return(MakePair(argv[0], argv[1]));
}

Define("car", CarPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("car", argc);
    PairArgCheck("car", argv[0]);

    return(First(argv[0]));
}

Define("cdr", CdrPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("cdr", argc);
    PairArgCheck("cdr", argv[0]);

    return(Rest(argv[0]));
}

Define("set-car!", SetCarPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("set-car!", argc);
    PairArgCheck("set-car!", argv[0]);

//    AsPair(argv[0])->First = argv[1];
    SetFirst(argv[0], argv[1]);

    return(NoValueObject);
}

Define("set-cdr!", SetCdrPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("set-cdr!", argc);
    PairArgCheck("set-cdr!", argv[0]);

//    AsPair(argv[0])->Rest = argv[1];
    SetRest(argv[0], argv[1]);

    return(NoValueObject);
}

Define("null?", NullPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("null?", argc);

    return(argv[0] == EmptyListObject ? TrueObject : FalseObject);
}

Define("list?", ListPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("list?", argc);

    return(ListType(argv[0]) == ProperList ? TrueObject : FalseObject);
}

Define("circular-list?", CircularListPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("circular-list?", argc);

    return(ListType(argv[0]) == CircularList ? TrueObject : FalseObject);
}

Define("dotted-list?", DottedListPPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("dotted-list?", argc);

    return(ListType(argv[0]) == DottedList ? TrueObject : FalseObject);
}

Define("make-list", MakeListPrimitive)(long_t argc, FObject argv[])
{
    OneOrTwoArgsCheck("make-list", argc);
    NonNegativeArgCheck("make-list", argv[0], 0);

    FObject obj = argc == 1 ? FalseObject : argv[1];
    FObject lst = EmptyListObject;
    long_t n = AsFixnum(argv[0]);

    while (n > 0)
    {
        lst = MakePair(obj, lst);
        n -= 1;
    }

    return(lst);
}

Define("list", ListPrimitive)(long_t argc, FObject argv[])
{
    FObject lst = EmptyListObject;
    long_t adx = argc;

    while (adx > 0)
    {
        adx -= 1;
        lst = MakePair(argv[adx], lst);
    }

    return(lst);
}

Define("length", LengthPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("length", argc);

    return(MakeFixnum(ListLength("length", argv[0])));
}

Define("length+", LengthPlusPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("length+", argc);

    long_t len = ListLengthPlus(argv[0]);
    if (len < 0)
        return(FalseObject);
    return(MakeFixnum(len));
}

static FObject ReverseList(const char * nam, FObject list)
{
    FObject rlst = EmptyListObject;
    FObject lst = list;

    while (lst != EmptyListObject)
    {
        PairArgCheck(nam, lst);

        rlst = MakePair(First(lst), rlst);
        lst = Rest(lst);
    }

    return(rlst);
}

Define("append", AppendPrimitive)(long_t argc, FObject argv[])
{
    if (argc == 0)
        return(EmptyListObject);

    FObject ret = argv[argc - 1];

    long_t adx = argc - 1;
    while (adx > 0)
    {
        adx -= 1;
        ListArgCheck("append", argv[adx]);
        FObject lst = ReverseList("append", argv[adx]);

        while (lst != EmptyListObject)
        {
            FAssert(PairP(lst));

            FObject obj = lst;
            lst = Rest(lst);
//            AsPair(obj)->Rest = ret;
            SetRest(obj, ret);
            ret = obj;
        }
  }

    return(ret);
}

Define("reverse", ReversePrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("reverse", argc);
    ListArgCheck("reverse", argv[0]);

    return(ReverseList("reverse", argv[0]));
}

Define("reverse!", ReverseBangPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("reverse!", argc);
    ListArgCheck("reverse!", argv[0]);

    return(ReverseListModify(argv[0]));
}

Define("list-tail", ListTailPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("list-tail", argc);
    ListArgCheck("list-tail", argv[0]);
    NonNegativeArgCheck("list-tail", argv[1], 0);

    FObject lst = argv[0];
    long_t k = AsFixnum(argv[1]);

    while (k > 0)
    {
        PairArgCheck("list-tail", lst);

        lst = Rest(lst);
        k -= 1;
    }

    return(lst);
}

Define("list-ref", ListRefPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("list-ref", argc);
    ListArgCheck("list-ref", argv[0]);
    NonNegativeArgCheck("list-ref", argv[1], 0);

    FObject lst = argv[0];
    long_t k = AsFixnum(argv[1]);

    while (k > 0)
    {
        PairArgCheck("list-ref", lst);

        lst = Rest(lst);
        k -= 1;
    }

    PairArgCheck("list-ref", lst);

    return(First(lst));
}

Define("list-set!", ListSetPrimitive)(long_t argc, FObject argv[])
{
    ThreeArgsCheck("list-set!", argc);
    ListArgCheck("list-set!", argv[0]);
    NonNegativeArgCheck("list-set!", argv[1], 0);

    FObject lst = argv[0];
    long_t k = AsFixnum(argv[1]);

    while (k > 0)
    {
        PairArgCheck("list-set!", lst);

        lst = Rest(lst);
        k -= 1;
    }

    PairArgCheck("list-set!", lst);

    SetFirst(lst, argv[2]);
    return(NoValueObject);
}

FObject Memq(FObject obj, FObject lst)
{
    while (PairP(lst))
    {
        if (EqP(First(lst), obj))
            return(lst);

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

Define("memq", MemqPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("memq", argc);
    ListArgCheck("memq", argv[1]);

    return(Memq(argv[0], argv[1]));
}

Define("memv", MemvPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("memv", argc);
    ListArgCheck("memv", argv[1]);

    FObject lst = argv[1];

    while (PairP(lst))
    {
        if (EqvP(First(lst), argv[0]))
            return(lst);

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

Define("%member", MemberPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("member", argc);
    ListArgCheck("member", argv[1]);

    FObject lst = argv[1];

    while (PairP(lst))
    {
        if (EqualP(First(lst), argv[0]))
            return(lst);

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

FObject Assq(FObject obj, FObject alst)
{
    while (PairP(alst))
    {
        FAssert(PairP(First(alst)));

        if (EqP(First(First(alst)), obj))
            return(First(alst));

        alst = Rest(alst);
    }

    FAssert(alst == EmptyListObject);

    return(FalseObject);
}

FObject Assoc(FObject obj, FObject alst)
{
    while (PairP(alst))
    {
        FAssert(PairP(First(alst)));

        if (EqualP(First(First(alst)), obj))
            return(First(alst));

        alst = Rest(alst);
    }

    FAssert(alst == EmptyListObject);

    return(FalseObject);
}

Define("assq", AssqPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("assq", argc);
    ListArgCheck("assq", argv[1]);

    FObject lst = argv[1];

    while (PairP(lst))
    {
        PairArgCheck("assq", First(lst));

        if (EqP(First(First(lst)), argv[0]))
            return(First(lst));

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

Define("assv", AssvPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("assv", argc);
    ListArgCheck("assv", argv[1]);

    FObject lst = argv[1];

    while (PairP(lst))
    {
        PairArgCheck("assv", First(lst));

        if (EqvP(First(First(lst)), argv[0]))
            return(First(lst));

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

Define("%assoc", AssocPrimitive)(long_t argc, FObject argv[])
{
    TwoArgsCheck("assoc", argc);
    ListArgCheck("assoc", argv[1]);

    FObject lst = argv[1];

    while (PairP(lst))
    {
        PairArgCheck("assoc", First(lst));

        if (EqualP(First(First(lst)), argv[0]))
            return(First(lst));

        lst = Rest(lst);
    }

    FAssert(lst == EmptyListObject);

    return(FalseObject);
}

Define("list-copy", ListCopyPrimitive)(long_t argc, FObject argv[])
{
    OneArgCheck("list-copy", argc);

    if (PairP(argv[0]) == 0)
        return(argv[0]);

    FObject lst = argv[0];
    FObject ret = MakePair(First(lst), NoValueObject);
    FObject nlst = ret;
    lst = Rest(lst);

    while (PairP(lst))
    {
        SetRest(nlst, MakePair(First(lst), NoValueObject));
        nlst = Rest(nlst);
        lst = Rest(lst);
    }

    SetRest(nlst, lst);
    return(ret);
}

FObject MakeTConc()
{
    FObject lp = MakePair(FalseObject, EmptyListObject);

    return(MakePair(lp, lp));
}

long_t TConcEmptyP(FObject tconc)
{
    FAssert(PairP(tconc));
    FAssert(PairP(First(tconc)));
    FAssert(PairP(Rest(tconc)));

    return(First(tconc) == Rest(tconc));
}

void TConcAdd(FObject tconc, FObject obj)
{
    FAssert(PairP(tconc));
    FAssert(PairP(Rest(tconc)));

    SetFirst(Rest(tconc), obj);
    SetRest(Rest(tconc), MakePair(FalseObject, EmptyListObject));
    SetRest(tconc, Rest(Rest(tconc)));
}

FObject TConcRemove(FObject tconc)
{
    FAssert(TConcEmptyP(tconc) == 0);
    FAssert(PairP(tconc));
    FAssert(PairP(First(tconc)));

    FObject obj = First(First(tconc));
    SetFirst(tconc, Rest(First(tconc)));

    return(obj);
}

static FObject Primitives[] =
{
    PairPPrimitive,
    ConsPrimitive,
    CarPrimitive,
    CdrPrimitive,
    SetCarPrimitive,
    SetCdrPrimitive,
    NullPPrimitive,
    ListPPrimitive,
    CircularListPPrimitive,
    DottedListPPrimitive,
    MakeListPrimitive,
    ListPrimitive,
    LengthPrimitive,
    LengthPlusPrimitive,
    AppendPrimitive,
    ReversePrimitive,
    ReverseBangPrimitive,
    ListTailPrimitive,
    ListRefPrimitive,
    ListSetPrimitive,
    MemqPrimitive,
    MemvPrimitive,
    MemberPrimitive,
    AssqPrimitive,
    AssvPrimitive,
    AssocPrimitive,
    ListCopyPrimitive
};

void SetupPairs()
{
    for (ulong_t idx = 0; idx < sizeof(Primitives) / sizeof(FPrimitive *); idx++)
        DefinePrimitive(Bedrock, BedrockLibrary, Primitives[idx]);
}
