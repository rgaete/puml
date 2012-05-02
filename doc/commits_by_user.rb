Users = {
  :Maxine => ['Maxine Major <gomaxxy@gmail.com>',
            'gomaxxy@gmail.com'],
  :Logan => ['Logan Evans <loganpevans@gmail.com>',
           'Logan Evans <d3veate@gmail.com>'],
  :Zach => ['Zachary Curtis <curt3897@vandals.uidaho.edu>',
          'Zach@Mini-Destroyer.ftrdhcpuser.net',
          'Zach',
          'highiq2@hotmail.com'],
  :Josh => ['Josh@Athena',
          'Josh Armstrong <theartistformerlyknownasjosh@gmail.com?',
          'Josh Armstrong <theartistformerlyknownasjosh@gmail.com>',
          'theartistformerlyknownasjosh@gmail.com'],
  :Brian => ['Brian Bowles <brian.bowles@gmail.com>',
           'Brian@LoveMachine.localdomain'],
  :Jeremy => ['Jeremy Klas <jeremyklas@gmail.com>',
            'Jeremy@Jeremy-Laptop',
            'Jeremy@Jeremy-Laptop.natnow.rr.com'],
  :Nate => ['Nate Krussel <nate.krussel@gmail.com>'],
  :David => ['David <well4536@vandals.uidaho.edu>',
           'David@David-PC.natnow.rr.com'],
  :Morgan => ['skinny.teddy.bear@gmail.com',
            'Morgan',
            'Morgan Weir <skinny.teddy.bear@gmail.com>']
}

def get_all_users
  users = []
  results = []
  %x/hg log -r 55:388 | grep user/.split("\n").each do |line|
    if line =~ /^user:\s*(.*)$/
      results << $1
    end
  end
  results.each do |line|
    users << line if !users.include? line
  end
  puts users
end

def puts_users
  Users.each_pair do |user, names|
    puts
    puts "User: #{user}"
    names.each do |name|
      puts name
    end
  end
end

def get_num_commits_for user
  count = 0
  Users[user].each do |name|
    count += %x(hg log -r 55:388 -u '#{name.to_s}' | grep user).split("\n").length
  end
  count
end

if __FILE__ == $0
    Users.each_pair do |user, names|
        puts "User: #{user.to_s} -- #{get_num_commits_for user}"
    end
end
