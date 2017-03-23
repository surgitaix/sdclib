cat "$1" | xsltproc remove_annotations.xsl - | xsltproc remove_comments.xsl - | sed 's/\t//g; s/\"/\\"/g' | tr -d '\n' | sed -r 's/(.{16000})/\1\n/g' > "$1.split"

