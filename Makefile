ENCODERBIN = encoder
DECODERBIN = decoder
LIBENCODER = ./encoder_dependencies/libencoder.a
LIBDECODER = ./decoder_dependencies/libdecoder.a
STD_DEPENDENCIES = ./std_dependencies/shared_memory_utils.c \
				   ./std_dependencies/min_heap_implementation.c \
				   ./std_dependencies/shared_memory_utils.c \
				   ./std_dependencies/semaphores_utils.c \
				   ./std_dependencies/get_huffman_tree.c \
				   ./std_dependencies/free_tree.c

SRCS_ENCODER = $(STD_DEPENDENCIES) \
			   ./encoder_dependencies/gathering_and_init_data.c \
			   ./encoder_dependencies/free_utils.c \
			   ./encoder_dependencies/send_decoder.c \
			   ./encoder_dependencies/destroy_blocks.c \
			   ./encoder_dependencies/compact_huff_code.c \
			   ./encoder_dependencies/get_info_decoder.c \
			   ./encoder_dependencies/merge_args.c \
			   ./encoder_dependencies/print_info.c \
			   ./encoder_dependencies/get_encoded_string.c

SRCS_DECODER = $(STD_DEPENDENCIES) \
			   ./decoder_dependencies/get_decoded_message.c \
			   ./decoder_dependencies/shared_memory_ops.c \
			   ./decoder_dependencies/send_info.c \
			   ./decoder_dependencies/unpack.c

OBJS_ENCODER = $(SRCS_ENCODER:%.c=%.o)
OBJS_DECODER = $(SRCS_DECODER:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -g3

all : $(ENCODERBIN) $(DECODERBIN)

$(ENCODERBIN) : $(LIBENCODER)
	cc $(FLAGS) ./encoder_dependencies/main.c -lpthread $(LIBENCODER) -o $@

$(DECODERBIN) : $(LIBDECODER)
	cc $(FLAGS) ./decoder_dependencies/main.c -lpthread $(LIBDECODER) -o $@

$(LIBENCODER) : $(OBJS_ENCODER)
	ar rcs $(LIBENCODER) $(OBJS_ENCODER)

$(LIBDECODER) : $(OBJS_DECODER)
	ar rcs $(LIBDECODER) $(OBJS_DECODER)

%.o : %.c
	cc $(FLAGS) -I ./ -c $< -o $@

clean :
	rm -rf $(OBJS_ENCODER) $(LIBENCODER) $(OBJS_DECODER) $(LIBDECODER)

fclean : clean
	rm -rf $(ENCODERBIN) $(DECODERBIN)

re : fclean all

rexec : fclean all
	./$(ENCODERBIN)
