$rel_loc = '../code'
up_one = File::split(Dir.pwd)[0]
up_two = File::split(up_one)[0]
$par_loc = File::join(up_two, 'code')
$out_loc = Dir.pwd

def san fname
    fname_copy = fname.clone
    # Need to "sanitize" files with spaces so that scripts will work
    fname_copy[fname_copy.index ' '] = '\ ' if fname_copy.index ' '
    fname_copy
end

def run
    puts 'cleaning directory...'

    Dir.entries($out_loc).each do |fname|
        %x/rm -r #{san(fname)}/ unless ['.', '..', 'pUML_doxy', 'run_doxy.rb'].include? fname
    end

    puts 'done cleaning.'

    Dir.entries($par_loc).each do |fname|
        if File::directory? File::join($par_loc, fname) and not ['.', '..'].include? fname
            run_file File::join($par_loc, fname)
        end
    end
end

def run_file fname
    puts "> run_file(#{fname})"

    outdir = File::join $out_loc, File::split(fname)[1].chomp
    %x/mkdir #{san(outdir)}/
    outdox = File::join outdir, 'doxy.tmp'

    mod_doxy outdox

    Dir.chdir fname
    %x/doxygen #{san(outdox)}/
    %x/rm #{san(outdox)}/
end

def mod_doxy outdox
    tmp_doxy = []

    File.open(outdox, 'w') do |outfile|
        File.new(File::join $out_loc, 'pUML_doxy').readlines.each do |line|
            if /^(OUTPUT_DIRECTORY).*(=) (.*)$/ =~ line
                line = "#{$1} #{$2} \"#{File::split(outdox)[0]}\""
            end

            outfile.write line
        end
    end
end


if __FILE__ == $0
    run
    #mod_doxy 
end
