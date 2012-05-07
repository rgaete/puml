def create_all datemin="2012-01-15", datemax="2012-05-11"
    %x/hg activity --showtags --datemin=#{datemin} --datemax=#{datemax} --width=1920 --height=1080 -o overall.png/
    %x/hg activity --showtags --split=authors --maxcaptions=9 --datemin=#{datemin} --datemax=#{datemax} --width=1920 --height=1080 -o authors.png/
    %x/hg activity --showtags --split=files --maxcaptions=9 --datemin=#{datemin} --datemax=#{datemax} --width=1920 --height=1080 -o files.png/
    %x/hg activity --showtags --split=directories --datemin=#{datemin} --datemax=#{datemax} --width=1920 --height=1080 -o directories.png/
end


if __FILE__ == $0
    create_all
end
