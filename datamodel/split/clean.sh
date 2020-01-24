cat "$1" | xsltproc remove_annotations.xsl - | xsltproc remove_comments.xsl - | sed "s/[ $(printf '\t')&]*$//" | sed "/^$/d" > "$1.split"

