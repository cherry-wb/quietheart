import subprocess
import re


class Adb (object):
    MAX_TRY = 1
    
    def __init__(self, device_id = None):
        self.device_id = device_id
        
    def run_cmd(self, cmd, max_retry = MAX_TRY, no_exception_raise=False):
        try_count = 0
        
        if self.device_id is not None:
            adb_cmd = "adb" + ' -s %s ' % self.device_id + ' ' + cmd
        else:
            adb_cmd = "adb" + ' ' + cmd
            
        while try_count < max_retry:
            try:
                output = subprocess.check_output(adb_cmd, shell = True)
                break
            except subprocess.CalledProcessError:
                if no_exception_raise:
                    return None
                try_count = try_count + 1
                if try_count >= max_retry:
                    raise

        return output
    
    def adb_shell(self, cmd, max_retry = MAX_TRY):
        return self.run_cmd('shell %s' % cmd, max_retry)
    
    def get_device_ids(self):
        ids = []
        lines = re.split("\n", self.run_cmd('devices'))
        valid = re.compile(r"(\S+)\s+device")
        for line in lines:
            m = valid.match(line)
            if m is not None:
                ids.append(m.group(1))
        return ids
    
    
    
    
