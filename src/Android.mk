LOCAL_PATH := $(call my-dir)

SF_SRC_FILES := \
    benchmark.cpp bitbase.cpp bitboard.cpp endgame.cpp evaluate.cpp main.cpp \
	material.cpp misc.cpp movegen.cpp movepick.cpp pawns.cpp position.cpp psqt.cpp \
	search.cpp thread.cpp timeman.cpp tt.cpp uci.cpp ucioption.cpp tune.cpp syzygy/tbprobe.cpp \
	nnue/evaluate_nnue.cpp nnue/features/half_ka_v2.cpp \
	partner.cpp parser.cpp piece.cpp variant.cpp xboard.cpp \
	nnue/features/half_ka_v2_variants.cpp

MY_ARCH_DEF :=
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
  MY_ARCH_DEF += -mthumb -march=armv7-a -mfloat-abi=softfp
endif
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
  MY_ARCH_DEF += -DIS_64BIT -DUSE_POPCNT -DUSE_NEON
endif
ifeq ($(TARGET_ARCH_ABI),x86_64)
  MY_ARCH_DEF += -DIS_64BIT -DUSE_SSE41 -msse4.1
endif

include $(CLEAR_VARS)
LOCAL_MODULE    := fairy_stockfish
LOCAL_SRC_FILES := $(SF_SRC_FILES)
LOCAL_CFLAGS    := -std=c++17 -stdlib=libc++ -DNNUE_EMBEDDING_OFF -DLARGEBOARDS -DPRECOMPUTED_MAGICS -DALLVARS $(MY_ARCH_DEF) -s -fPIE
LOCAL_LDFLAGS	+= -s -fPIE -pie

include $(BUILD_EXECUTABLE)
#include $(BUILD_SHARED_LIBRARY)