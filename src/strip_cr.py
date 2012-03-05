import os
import sys

if __name__ == '__main__':
    for item in os.listdir('.'):
      if item.endswith('.cpp') or item.endswith('.h'):
        os.system('cat {0} | tr -d "\r" > {0}.tmp'.format(item))
        os.system('mv {0}.tmp {0}'.format(item))
