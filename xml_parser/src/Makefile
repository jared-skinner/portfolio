BUILDDIR=../bin
INCLUDE=-Iinclude

xml_parser: xml_parser.c
	$(CC) $? $(INCLUDE) -o $(BUILDDIR)/$@

clean:
	rm -f $(BUILDDIR)/* *.obj
