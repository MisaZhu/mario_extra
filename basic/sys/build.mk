
SYS_OBJS= $(mario_OBJS) $(mario_js_OBJS) \
	$(SYS)/native_sys.o \
	$(SYS)/system/native_system.o \
	$(SYS)/socket/native_socket.o  \
	$(SYS)/fs/native_fs.o \
	$(SYS)/dir/native_dir.o \
	$(SYS)/dns/dnsc.o $(SYS)/dns/query.o $(SYS)/dns/request.o $(SYS)/dns/response.o $(SYS)/dns/native_dns.o

SYS_TARGET=$(SYS)/native_$(SYS).so

$(SYS_TARGET): $(SYS_OBJS)
	$(LD) -shared -o $(SYS_TARGET) $(SYS_OBJS) $(LDFLAGS)

CLEAN += $(SYS_TARGET) $(SYS_OBJS)

