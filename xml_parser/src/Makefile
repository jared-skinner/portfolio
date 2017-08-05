BUILDDIR=../bin
INCLUDE=-Iinclude

xml_parser: xml_parser.c interactive_shell.c node_navigation.c
	$(CC) $? $(INCLUDE) -o $(BUILDDIR)/$@

clean:
	rm -f $(BUILDDIR)/* *.obj
