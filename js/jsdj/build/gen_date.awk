#
# This requires -vpackage_name=whatever.the.name.of.the.package.is
#

BEGIN{
print
print "// generated automatically by gen_date.awk"
print
print "package "package_name";" 
print
print "class BuildDate"
print "{"
print strftime("    // %A, %B %d, %Y at %I:%M %p");
print
print "    public static final long buildDate = " systime() "000L;"
print
print "    public static final java.util.Date date()"
print "    {"
print "        return new java.util.Date(buildDate);"
print "    }"
print
print "    public static final String display()"
print "    {"
print "        return date().toString();"
print "    }"
print "}"
}




