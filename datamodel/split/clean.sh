cat "$1" | xsltproc remove_annotations.xsl - | xsltproc remove_comments.xsl - > "$1.split"

