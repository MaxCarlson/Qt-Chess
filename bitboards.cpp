#include "bitboards.h"

#include <iostream>

const U64 FileABB = 0x0101010101010101ULL;
const U64 FileBBB = FileABB << 1;
const U64 FileCBB = FileABB << 2;
const U64 FileDBB = FileABB << 3;
const U64 FileEBB = FileABB << 4;
const U64 FileFBB = FileABB << 5;
const U64 FileGBB = FileABB << 6;
const U64 FileHBB = FileABB << 7;

//totally full bitboard
const U64 full  = 0xffffffffffffffffULL;
const U64 Totallyempty = 0;

//files to keep pieces from moving left or right off board
extern const U64 notAFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
extern const U64 notHFile = 0xfefefefefefefefe; // ~0x0101010101010101

extern const U64 rank4 = 1095216660480L;
extern const U64 rank5=4278190080L;

//board for knight moves that can be shifted
extern const U64 KNIGHT_SPAN=43234889994L;

    //files for keeping knight moves from wrapping
extern const U64 FILE_AB=FileABB + FileBBB;
extern const U64 FILE_GH=FileGBB + FileHBB;

//Bitboard of all king movements that can then be shifted
extern const U64 KING_SPAN=460039L;

//board showing where all pieces are + aren't
extern U64 FullTiles;
extern U64 EmptyTiles;

extern U64 BBWhitePieces;

extern U64 BBWhitePawns;
extern U64 BBWhiteRooks;
extern U64 BBWhiteKnights;
extern U64 BBWhiteBishops;
extern U64 BBWhiteQueens;
extern U64 BBWhiteKing;


extern U64 BBBlackPieces;

extern U64 BBBlackPawns;
extern U64 BBBlackRooks;
extern U64 BBBlackKnights;
extern U64 BBBlackBishops;
extern U64 BBBlackQueens;
extern U64 BBBlackKing;

extern const U64 RankMasks8[8] =/*from rank1 to rank8*/
    {
        0xFFL, 0xFF00L, 0xFF0000L, 0xFF000000L, 0xFF00000000L, 0xFF0000000000L, 0xFF000000000000L, 0xFF00000000000000L
    };
extern const U64 FileMasks8[8] =/*from fileA to FileH*/
{
    0x101010101010101L, 0x202020202020202L, 0x404040404040404L, 0x808080808080808L,
    0x1010101010101010L, 0x2020202020202020L, 0x4040404040404040L, 0x8080808080808080L
};

extern const U64 DiagonalMasks8[15] =/*from top left to bottom right*/
{
0x1L, 0x102L, 0x10204L, 0x1020408L, 0x102040810L, 0x10204081020L, 0x1020408102040L,
0x102040810204080L, 0x204081020408000L, 0x408102040800000L, 0x810204080000000L,
0x1020408000000000L, 0x2040800000000000L, 0x4080000000000000L, 0x8000000000000000L
};

extern const U64 AntiDiagonalMasks8[15] =/*from top right to bottom left*/
{
0x80L, 0x8040L, 0x804020L, 0x80402010L, 0x8040201008L, 0x804020100804L, 0x80402010080402L,
0x8040201008040201L, 0x4020100804020100L, 0x2010080402010000L, 0x1008040201000000L,
0x804020100000000L, 0x402010000000000L, 0x201000000000000L, 0x100000000000000L
};



U64 FullTiles;
U64 EmptyTiles;

U64 BBWhitePieces;

U64 BBWhitePawns;
U64 BBWhiteRooks;
U64 BBWhiteKnights;
U64 BBWhiteBishops;
U64 BBWhiteQueens;
U64 BBWhiteKing;


U64 BBBlackPieces;

U64 BBBlackPawns;
U64 BBBlackRooks;
U64 BBBlackKnights;
U64 BBBlackBishops;
U64 BBBlackQueens;
U64 BBBlackKing;

std::string chessBoard [8][8]= {
    {"r", "n", "b", "q", "k", "b", "n", "r"},
    {"p", "p", "p", "p", "p", "p", "p", "p",},
    {" ", " ", " ", "r", " ", "b", " ", " "},
    {" ", " ", " ", "P", "P", " ", " ", " "},
    {" ", "r", "P", "K", " ", "P", "q", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"R", "N", "B", "Q", " ", "B", "N", "R"},
              };


BitBoards::BitBoards()
{

}

std::string BitBoards::generatePsMoves()
{
    std::string moves;

    //moves += possiblePW(BBWhitePawns, EmptyTiles);
    //moves += possiblePB(BBBlackPawns, EmptyTiles);
    //U64 a = horizVert(20);
    //U64 a = DAndAntiDMoves(20);
   // std::string a = possibleWN(BBWhiteKnights, BBWhitePieces, BBBlackKing);
    //std::string b = possibleBN(BBBlackKnights, BBBlackPieces, BBWhiteKing);
    //std::string d = possibleK(BBWhiteKing, BBWhitePieces);
    //U64 a = unsafeForBlack(BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //U64 b = unsafeForWhite(BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //std::string f = possibleMovesW(BBWhitePieces, BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //std::string g = possibleMovesB(BBBlackPieces, BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //U64 a = pinnedBB(BBBlackRooks, BBBlackBishops, BBBlackQueens, BBWhiteKing);
    std::string f = possibleMovesW(BBWhitePieces, BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    int c = 5;

    /*
    for(int i = 0; i < 64; i++){
        if(a & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }*/


}

//move generation functions for white and black
std::string BitBoards::possibleMovesW(U64 whitepieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;
    U64 empty =~ FullTiles, pinned, kingSafeLessKing;
    std::string moveList;
    //generate pinned BB and remove pieces from it for sepperate move gen ~~ opposite piece color aside from king
    pinned = pinnedBB(brooks, bbishops, bqueens, wking);
    moveList += pinnedMoves(pinned, wpawns, wrooks, wbishops, wqueens, wking, brooks, bbishops, bqueens, whitepieces, true);

    moveList += possibleWP(wpawns, empty, bking);
    moveList += possibleR(wrooks, whitepieces, bking);
    moveList += possibleN(wknights, whitepieces, bking);
    moveList += possibleB(wbishops, whitepieces, bking);
    moveList += possibleQ(wqueens, whitepieces, bking);
    //generate king safety array without king in it, pass to king move gen (blank board in place of our king)
    kingSafeLessKing = unsafeForWhite(wpawns, wrooks, wknights, wbishops, wqueens, 0LL, bpawns, brooks, bknights, bbishops, bqueens, bking);
    //generates legal king moves
    moveList += possibleK(wking, whitepieces, kingSafeLessKing);
    //int temp = moveList.length()/4;
    return moveList;
}

std::string BitBoards::possibleMovesB(U64 blackpieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;
    U64 empty =~ FullTiles, pinned, kingSafeLessKing;
    std::string moveList;
    //generate pinned BB and remove pieces from it for sepperate move gen ~~ opposite piece color aside from king
    pinned = pinnedBB(wrooks, wbishops, wqueens, bking);

    moveList += possibleBP(bpawns, empty, wking);
    moveList += possibleR(brooks, blackpieces, wking);
    moveList += possibleN(bknights, blackpieces, wking);
    moveList += possibleB(bbishops, blackpieces, wking);
    moveList += possibleQ(bqueens, blackpieces, wking);

    //generate king safety array without king in it, pass to king move gen (0LL in place of our king)
    kingSafeLessKing = unsafeForBlack(wpawns, wrooks, wknights, wbishops, wqueens, wking, bpawns, brooks, bknights, bbishops, bqueens, 0LL);
    moveList += possibleK(bking, blackpieces, kingSafeLessKing);
    //int temp = moveList.length()/4;
    return moveList;
}

U64 BitBoards::unsafeForWhite(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    U64 unsafe;
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;

    //pawn
    unsafe = ((bpawns << 7) &~ FileHBB); //pawn capture right
    unsafe |= ((bpawns << 9) &~ FileABB); // left

    U64 possibles;
    //knights
    U64 i = bknights &~(bknights - 1);

    while (i != 0){
        int iLocation = trailingZeros(i);
        if(iLocation > 18){
            possibles = KNIGHT_SPAN << (iLocation - 18);
        } else {
            possibles = KNIGHT_SPAN >> (18 - iLocation);
        }

        if(iLocation % 8 < 4){
            possibles &= ~ FILE_GH;
        } else {
            possibles &= ~ FILE_AB;
        }
        unsafe |= possibles;
        bknights &= ~i;
        i = bknights &~ (bknights - 1);
    }
    //bishops / queens
    U64 QB = bqueens | bbishops;
    i = QB &~ (QB-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = DAndAntiDMoves(iLocation);
        unsafe |= possibles;
        QB &= ~i;
        i = QB &~ (QB-1);
    }

    //rooks / queens
    U64 QR = bqueens | brooks;
    i = QR &~ (QR-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = horizVert(iLocation);
        unsafe |= possibles;
        QR &= ~i;
        i = QR &~ (QR-1);
    }

    //king
    int iLocation = trailingZeros(bking);
    if(iLocation > 9){
        possibles = KING_SPAN << (iLocation-9);
    } else {
        possibles = KING_SPAN >> (9 - iLocation);
    }

    if(iLocation % 8 < 4){
        possibles &= ~ FILE_GH;
    } else {
        possibles &= ~ FILE_AB;
    }
    unsafe |= possibles;
    //drawBB(unsafe);

    return unsafe;
}

U64 BitBoards::unsafeForBlack(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishop, U64 bqueens, U64 bking)
{
    U64 unsafe;
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishop | bqueens | bking;

    //pawn
    unsafe = ((wpawns << 7) &~ FileABB); //pawn capture right
    unsafe |= ((wpawns << 9) &~ FileHBB); // left

    U64 possibles;
    //knights
    U64 i = wknights &~(wknights - 1);

    while (i != 0){
        int iLocation = trailingZeros(i);
        if(iLocation > 18){
            possibles = KNIGHT_SPAN << (iLocation - 18);
        } else {
            possibles = KNIGHT_SPAN >> (18 - iLocation);
        }

        if(iLocation % 8 < 4){
            possibles &= ~ FILE_GH;
        } else {
            possibles &= ~ FILE_AB;
        }
        unsafe |= possibles;
        wknights &= ~i;
        i = wknights &~ (wknights - 1);
    }
    //bishops / queens
    U64 QB = wqueens | wbishops;
    i = QB &~ (QB-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = DAndAntiDMoves(iLocation);
        unsafe |= possibles;
        QB &= ~i;
        i = QB &~ (QB-1);
    }

    //rooks / queens
    U64 QR = wqueens | wrooks;
    i = QR &~ (QR-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = horizVert(iLocation);
        unsafe |= possibles;
        QR &= ~i;
        i = QR &~ (QR-1);
    }

    //king
    int iLocation = trailingZeros(wking);
    if(iLocation > 9){
        possibles = KING_SPAN << (iLocation-9);
    } else {
        possibles = KING_SPAN >> (9 - iLocation);
    }

    if(iLocation % 8 < 4){
        possibles &= ~ FILE_GH;
    } else {
        possibles &= ~ FILE_AB;
    }
    unsafe |= possibles;
    //drawBB(unsafe);

    return unsafe;
}
//first function calc pieces pinned between sliders and king second calcs pinned piece moves
U64 BitBoards::pinnedBB(U64 rooks, U64 bishops, U64 queens, U64 king)
{
    U64 pinned  = 0LL, uB, dB, rB, lB, nEB, nWB, sWB, sEB, tempRay, oneP;
    //function for finding pinned pieces and later removing them from normal move pool
    //in order to generate their moves only along their pinned ray

    //NOTE!!! return for loops to while(i!=0) loops for faster code

    //king up ray
    uB = up(king);
    //king down ray
    dB = down(king);
    //king right ray
    rB = right(king);
    //king ray left
    lB = left(king);
    //king NE ray
    nEB = upright(king);
    //king SE ray
    sEB = downright(king);
    //king SW ray
    sWB = downleft(king);
    //king NW ray
    nWB = upleft(king);


    //rooks / queens
    U64 QR = queens | rooks;
    for(int j = 0; j < 64; j++){
        oneP = 0LL;
        if( QR & (1ULL << j)){
            oneP += (1ULL << j);
            //calculate horiz and vert rays
            tempRay = up(oneP); // up qb ray
            pinned |= dB & tempRay; // merge with down k
            tempRay = down(oneP); //down qb
            pinned |= uB & tempRay; // merge with up k
            tempRay = right(oneP); //right qb
            pinned |= lB & tempRay; // left k
            tempRay = left(oneP); // left qb
            pinned |= rB & tempRay; // right k
        }

    }
    //drawBB(pinned);
    //bishops / queens
    U64 QB = queens | bishops;
    for(int j = 0; j < 64; j++){
        oneP = 0LL;
        if( QB & (1ULL << j)){
            oneP += (1ULL << j);
            //calculate all diagonal moves
            tempRay = upright(oneP); //up right qb
            pinned |= sWB & tempRay; //down left k
            tempRay = downright(oneP);
            pinned |= nWB & tempRay; // up left
            tempRay = downleft(oneP);
            pinned |= nEB & tempRay;
            tempRay = upleft(oneP);
            pinned |= sEB & tempRay;
        }
    }

    //drawBB(pinned);

    //drawBB(upB);
    return pinned;
}

std::string BitBoards::pinnedMoves(U64 pinned, U64 opawns, U64 orooks, U64 obishops, U64 oqueens, U64 oking, U64 erooks, U64 ebishops, U64 equeens, U64 ourPieces, bool isWhite)
{
    //store full tiles so we can restore it to real later
    U64 tempStoreTiles = FullTiles;
    //king rays and enemy rays
    U64 uB, dB, rB, lB, nEB, nWB, sWB, sEB, tempRay, oneP, mrays = 0LL;
    //BB mask without pinned pieces in order to find possible moves
    FullTiles = FullTiles & ~pinned;

    std::string moves;

    //calculate move rays from enemy to king wihtout pinned pieces in the way

    //king up ray
    uB = up(oking);
    //king down ray
    dB = down(oking);
    //king right ray
    rB = right(oking);
    //king ray left
    lB = left(oking);
    //king NE ray
    nEB = upright(oking);
    //king SE ray
    sEB = downright(oking);
    //king SW ray
    sWB = downleft(oking);
    //king NW ray
    nWB = upleft(oking);


    //rooks / queens
    U64 QR = equeens | erooks;
    for(int j = 0; j < 64; j++){
        oneP = 0LL;
        if( QR & (1ULL << j)){
            oneP += (1ULL << j);
            //calculate horiz and vert rays
            tempRay = up(oneP); // up qb ray
            mrays |= dB & tempRay; // merge with down k
            tempRay = down(oneP); //down qb
            mrays |= uB & tempRay; // merge with up k
            tempRay = right(oneP); //right qb
            mrays |= lB & tempRay; // left k
            tempRay = left(oneP); // left qb
            mrays |= rB & tempRay; // right k
        }

    }
    //drawBB(mrays);
    //drawBB(pinned);
    //bishops / queens
    U64 QB = equeens | ebishops;
    for(int j = 0; j < 64; j++){
        oneP = 0LL;
        if( QB & (1ULL << j)){
            oneP += (1ULL << j);
            //calculate all diagonal moves
            tempRay = upright(oneP); //up right qb
            mrays |= sWB & tempRay; //down left k
            tempRay = downright(oneP);
            mrays |= nWB & tempRay; // up left
            tempRay = downleft(oneP);
            mrays |= nEB & tempRay;
            tempRay = upleft(oneP);
            mrays |= sEB & tempRay;
        }
    }


    //restore accurate full tiles
    FullTiles = tempStoreTiles;


    U64 enemyPieces = ~ourPieces & FullTiles;

    //only check pinned pieces
    //pawns
    opawns = opawns & pinned;
    moves += pinnedPawnCaptures(opawns, enemyPieces, mrays, isWhite);
    //bishops
    obishops = obishops & pinned;
    moves += pinnedBishopMoves(obishops, ourPieces, mrays);
    //rooks

    //queens


    drawBB(enemyPieces);
    return moves;

}

std::string BitBoards::pinnedPawnCaptures(U64 opawns, U64 enemyPieces, U64 mrays, bool isWhite)
{
    std::string moves;
    //pinned pawn captures
    U64 PAWN_MOVES;
    if(isWhite == true){
        //capture right
        PAWN_MOVES = noEaOne(opawns) & enemyPieces & mrays;
        for(int i = 0; i < 64; i++){
            if(((PAWN_MOVES>>i)&1)==1){
                moves+=i%8-1;
                moves+=i/8+1;
                moves+=i%8;
                moves+=i/8;

            }
        }

        //capture left
        PAWN_MOVES = noWeOne(opawns) & enemyPieces & mrays;
        for(int i = 0; i < 64; i++){
            if(((PAWN_MOVES>>i)&1)==1){
                moves+=i%8+1;
                moves+=i/8+1;
                moves+=i%8;
                moves+=i/8;

            }
        }
    } else {
        //capture right
        PAWN_MOVES = soEaOne(opawns) & enemyPieces & mrays;
        for(int i = 0; i < 64; i++){
            if(((PAWN_MOVES>>i)&1)==1){
                moves+=i%8-1;
                moves+=i/8-1;
                moves+=i%8;
                moves+=i/8;

            }
        }

        //capture left
        PAWN_MOVES = soWeOne(opawns) & enemyPieces & mrays;
        for(int i = 0; i < 64; i++){
            if(((PAWN_MOVES>>i)&1)==1){
                moves+=i%8+1;
                moves+=i/8-1;
                moves+=i%8;
                moves+=i/8;

            }
        }
        return moves;
    }
}

std::string BitBoards::pinnedBishopMoves(U64 obishops, U64 ourPieces, U64 mrays)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((obishops>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) & ~ourPieces & mrays;
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}
//single ray direction functions -- mostly for pinned piece calcs
U64 BitBoards::up(U64 piece)
{
    U64 upB = piece;
    for(int i = 0; i < 8; i++){
        if((upB >> 8) & FullTiles){
            upB = upB | (upB >> 8);
            break;
        }
        upB = upB | (upB >> 8);
    }
    return upB;
}

U64 BitBoards::down(U64 piece)
{
    U64 dB = piece;
    for(int i = 0; i < 8; i++){
        if((dB << 8) & FullTiles){
            dB = dB | (dB << 8);
            break;
        }
        dB = dB | (dB << 8);
    }
    return dB;
}

U64 BitBoards::right(U64 piece)
{
    U64 rB = piece;
    for(int i = 0; i < 8; i++){
        if ((rB << 1) & FileABB){
            break;
        }
        if((rB << 1) & FullTiles){
            rB = rB | (rB << 1);
            break;
        }
        rB = rB | (rB << 1);
    }
    return rB;
}

U64 BitBoards::left(U64 piece)
{
    U64 lB = piece;
    for(int i = 0; i < 8; i++){
        if ((lB >> 1) & FileHBB){
            break;
        }
        if((lB >> 1) & FullTiles){
            lB = lB | (lB >> 1);
            break;
        }
        lB = lB | (lB >> 1);
    }
    return lB;
}

U64 BitBoards::upright(U64 piece)
{
    U64 nEB = piece;
    for(int i = 0; i < 8; i++){
        if((nEB >> 7) & FileABB){
            break;
        }
        if((nEB >> 7) & FullTiles){
            nEB |= nEB >> 7;
            break;
        }
        nEB |= nEB >> 7;
    }
    return nEB;
}

U64 BitBoards::downright(U64 piece)
{
    U64 sEB = piece;
    for(int i = 0; i < 8; i++){
        if((sEB << 9) & FileABB){
            break;
        }
        if((sEB << 9) & FullTiles){
            sEB |= sEB << 9;
            break;
        }
        sEB |= sEB << 9;
    }
    return sEB;
}

U64 BitBoards::downleft(U64 piece)
{
    U64 sWB = piece;
    for(int i = 0; i < 8; i++){
        if((sWB << 7) & FileHBB){
            break;
        }
        if((sWB << 7) & FullTiles){
            sWB |= sWB << 7;
            break;
        }
        sWB |= sWB << 7;
    }
    return sWB;
}

U64 BitBoards::upleft(U64 piece)
{
    U64 nWB = piece;
    for(int i = 0; i < 8; i++){
        if((nWB >> 9) & FileHBB){
            break;
        }
        if((nWB >> 9) & FullTiles){
            nWB |= nWB >> 9;
            break;
        }
        nWB |= nWB >> 9;
    }
    return nWB;
}

//pawn moves
std::string BitBoards::possibleWP(U64 wpawns, U64 EmptyTiles, U64 blackking)
{
    std::string list= "";

    //forward one
    U64 PAWN_MOVES = northOne(wpawns) & EmptyTiles;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }

    //forward two
    PAWN_MOVES = (wpawns>>16) & EmptyTiles &(EmptyTiles>>8) &rank4;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8+2;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture right
    PAWN_MOVES = noEaOne(wpawns) & BBBlackPieces & ~blackking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = noWeOne(wpawns) & BBBlackPieces & ~blackking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }
    return list;
}

std::string BitBoards::possibleBP(U64 bpawns, U64 EmptyTiles, U64 whiteking)
{
    std::string list= "";

    //forward one
    U64 PAWN_MOVES = southOne(bpawns) & EmptyTiles;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            //list+=""+(i/8+1)+(i%8)+(i/8)+(i%8);
            list+=i%8;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }

    //forward two
    PAWN_MOVES = (bpawns<<16) & EmptyTiles &(EmptyTiles<<8) & rank5;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8-2;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture right
    PAWN_MOVES = soEaOne(bpawns) & BBWhitePieces & ~whiteking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = soWeOne(bpawns) & BBWhitePieces & ~whiteking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }
    return list;
}

//other piece moves
std::string BitBoards::possibleR(U64 wOrBrooks, U64 wOrBpieces, U64 oppositeking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wOrBrooks>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = horizVert(i) & ~wOrBpieces & ~oppositeking;
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleB(U64 wOrBbishops, U64 wOrBpieces, U64 oppositeking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wOrBbishops>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) & ~wOrBpieces & ~oppositeking;
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;

}

std::string BitBoards::possibleN(U64 wOrBknights, U64 wOrBpieces, U64 oppositeking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wOrBknights>>i) &1) == 1){
            //use the knight span board which holds possible knight moves
            //and apply a shift to the knights current pos
            if(i > 18){
                moves = KNIGHT_SPAN<<(i-18);
            } else {
                moves = KNIGHT_SPAN>>(18-i);
            }

            //making sure the moves don't warp around to other side once shifter
            //as well as friendly and illegal king capture check
            if(i % 8 < 4){
                moves &= ~FILE_GH & ~wOrBpieces & ~oppositeking;
            } else {
                moves &= ~FILE_AB & ~wOrBpieces & ~oppositeking;
            }
            //testing -- draw moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleQ(U64 wOrBqueens, U64 wOrBpieces, U64 oppositeking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wOrBqueens>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) + horizVert(i) & ~wOrBpieces & ~oppositeking;
            //TEST drawing moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleK(U64 wOrBking, U64 wOrBpieces, U64 kingSafeLessKing)
{
    std::string list;
    U64 moves, safeBB;

    //use safety of king board without king in it, so king can't move to a "safe" area
    // opposite a potential ray piece

    int i = trailingZeros(wOrBking);
    if(i > 9){
        moves = KING_SPAN << (i-9);

    } else {
        moves = KING_SPAN >> (9-i);
    }

    if(i % 8 < 4){
        moves &= ~FILE_GH & ~wOrBpieces;

    } else {
        moves &= ~FILE_AB & ~wOrBpieces;
    }
    //check king unsafe board against king moves
    //removing places the king would be unsafe from the moves
    moves &= ~kingSafeLessKing;
    //drawBB(kingSafeLessKing);
    //drawBB(moves);
    U64 j = moves &~(moves-1);

    while(j != 0){
        int index = trailingZeros(j);

        list += i%8;
        list += i/8;
        list += index%8;
        list += index/8;

        moves &= ~j;
        j = moves &~ (moves-1);
    }

return list;

}


//implament into other MOVE GEN ASIDE FROM KINGS, MUCH FASTER THAN for 64 loop
int BitBoards::trailingZeros(U64 i)
{
    if (i == 0) return 64;
    U64 x = i;
    U64 y;
    int n = 63;
    y = x << 32; if (y != 0) { n -= 32; x = y; }
    y = x << 16; if (y != 0) { n -= 16; x = y; }
    y = x <<  8; if (y != 0) { n -=  8; x = y; }
    y = x <<  4; if (y != 0) { n -=  4; x = y; }
    y = x <<  2; if (y != 0) { n -=  2; x = y; }
    return (int) ( n - ((x << 1) >> 63));
}

U64 BitBoards::horizVert(int s)
{
    //convert slider location to 64 bit binary
    U64 binaryS = 1LL << s;

    //left and right moves
    U64 possibilitiesHorizontal = (FullTiles - 2 * binaryS) ^ ReverseBits(ReverseBits(FullTiles) - 2 * ReverseBits(binaryS));
    //moves up and down
    U64 possibilitiesVertical = ((FullTiles & FileMasks8[s % 8]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & FileMasks8[s % 8]) - (2 * ReverseBits(binaryS)));

    //NOTE need to & against friendlys. Incomplete mask of moves
    return (possibilitiesHorizontal & RankMasks8[s / 8]) | (possibilitiesVertical & FileMasks8[s % 8]);

}

U64 BitBoards::DAndAntiDMoves(int s)
{
    U64 binaryS = 1LL <<s;

    U64 possibilitiesDiagonal = ((FullTiles & DiagonalMasks8[(s / 8) + (s % 8)]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & DiagonalMasks8[(s / 8) + (s % 8)]) - (2 * ReverseBits(binaryS)));

    U64 possibilitiesAntiDiagonal = ((FullTiles & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]) - (2 * ReverseBits(binaryS)));

    return (possibilitiesDiagonal & DiagonalMasks8[(s / 8) + (s % 8)]) | (possibilitiesAntiDiagonal & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]);
}

U64 BitBoards::ReverseBits(U64 input)
{
    U64 output = input;
    for (int i = sizeof(input) * 8-1; i; --i)
    {
        output <<= 1;
        input  >>= 1;
        output |=  input & 1;
    }
    return output;
}


U64 BitBoards::northOne(U64 b)
{
    return b >> 8;
}

U64 BitBoards::southOne(U64 b)
{
    return b << 8;
}

U64 BitBoards::eastOne (U64 b)
{
    return (b << 1) & notHFile;
}

U64 BitBoards::noEaOne(U64 b)
{
    return (b >> 7) & notHFile;;
}

U64 BitBoards::soEaOne(U64 b)
{
    return (b << 9) & notHFile;
}

U64 BitBoards::westOne(U64 b)
{
    return (b >> 1) & notAFile;
}

U64 BitBoards::soWeOne(U64 b)
{

    return (b << 7) & notAFile;
}

U64 BitBoards::noWeOne(U64 b)
{
    return (b >> 9) & notAFile;
}


void BitBoards::constructBoards()
{
    //seed bitboards
    for(int i = 0; i < 64; i++){
        if(chessBoard[i/8][i%8] == "P"){
            BBWhitePawns += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "R"){
            BBWhiteRooks += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "N"){
            BBWhiteKnights += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "B"){
            BBWhiteBishops += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "Q"){
            BBWhiteQueens += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "K"){
            BBWhiteKing += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "p"){
            BBBlackPawns += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "r"){
            BBBlackRooks += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "n"){
            BBBlackKnights += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "b"){
            BBBlackBishops += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "q"){
            BBBlackQueens += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "k"){
            BBBlackKing += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }

    }

    //mark emtpy tiles with 1's
    EmptyTiles = ~(EmptyTiles ^ FullTiles);

    //testing!!!
    //EmptyTiles = noWeOne(EmptyTiles);

    for(int i = 0; i < 64; i++){
        if(EmptyTiles & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }
    std::cout << std::endl;
}

void BitBoards::drawBB(U64 board)
{
    for(int i = 0; i < 64; i++){
        if(board & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }
    std::cout<< std::endl;
}

























