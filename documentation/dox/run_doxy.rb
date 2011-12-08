$rel_loc = '../code'
up_one = File::split(Dir.pwd)[0]
up_two = File::split(up_one)[0]
$par_loc = File::join(up_two, 'code')
$out_loc = Dir.pwd

puts "par: #{$par_loc} -- out: #{$out_loc}"
puts '--------'

def run
    puts '> run'

    puts 'cleaning directory...'

    Dir.entries($out_loc).each do |fname|
        %x/rm -r #{fname}/ if ['.', '..', 'pUML_doxy', 'run_doxy.rb'].include? fname
    end

    puts 'done cleaning.'

    Dir.entries($par_loc).each do |fname|
        fname[fname.index ' '] = '\ ' if fname.index ' '
        if File::directory? File::join($par_loc, fname) and not ['.', '..'].include? fname
            run_file File::join($par_loc, fname)
        end
    end
    puts '< run'
end

def run_file fname
    outdir = File::join $out_loc, File::split(fname)[1].chomp
    %x/mkdir #{outdir}/
    outdox = File::join outdir, 'doxy.tmp'

    mod_doxy outdox

    Dir.chdir fname
    puts 'doxygen pUML_doxy.tmp...'
#    %x/doxygen pUML_doxy.tmp/
end

def mod_doxy outdox
    puts '> mod_doxy'
    tmp_doxy = []

    File.open(outdox, 'w') do |outfile|
        File.new(File::join $out_loc, 'pUML_doxy').readlines.each do |line|
            if /^(OUTPUT_DIRECTORY).*(=) (.*)$/ =~ line
                line = "#{$1} #{$2} #{outdox}"
            end

            outfile.write line
        end
    end

    #tmp_doxy = File.new(File::join $out_loc, trimmed_fname).readlines
    puts 'rm pUML_doxy.tmp...'
#    %x/rm pUML_doxy.tmp/
    puts '< mod_doxy'
end

glob = Dir.entries '.'


#glob.each {|f| puts "#{f} --- #{File::directory?(File::join(rel_loc,f))}"}


if __FILE__ == $0
    run
    #mod_doxy 
end
