EXE_DECODER = decoder
EXE_ENCODER = encoder
EXE_PRINTER = print_as_ascii
EXE_VIEWTREE = view_tree

TEST = test

TERM = sp2019

all: $(EXE_DECODER) $(EXE_ENCODER) $(EXE_PRINTER) $(EXE_VIEWTREE)

OBJS = huffman_tree.o frequency.o encoder.o decoder.o binary_file_writer.o binary_file_reader.o

# Use the CS 225 Makefile template
include cs225/make/cs225.mk

# Additional executables
OBJS_PROVIDED = $(OBJS_DIR)/huffman_tree.o $(OBJS_DIR)/frequency.o $(OBJS_DIR)/encoder.o $(OBJS_DIR)/decoder.o $(OBJS_DIR)/binary_file_reader.o $(OBJS_DIR)/binary_file_writer.o

$(EXE_DECODER): $(OBJS_PROVIDED) $(OBJS_DIR)/decoder_prog.o
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_ENCODER): $(OBJS_PROVIDED) $(OBJS_DIR)/encoder_prog.o
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_PRINTER): $(OBJS_PROVIDED) $(OBJS_DIR)/print_as_ascii.o
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_VIEWTREE): $(OBJS_PROVIDED) $(OBJS_DIR)/view_tree.o
	$(LD) $^ $(LDFLAGS) -o $@

data:
	curl -O https://courses.engr.illinois.edu/cs225/$(TERM)/assets/assignments/labs/huffman/lab_huffman_data.tar && tar -xf lab_huffman_data.tar && rm lab_huffman_data.tar
