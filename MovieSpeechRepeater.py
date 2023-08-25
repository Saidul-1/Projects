#Enhance video comprehension with our program that utilizes subtitle timeframes to replay each speech segment twice while the rest plays once. 
#Perfect for language learners and content understanding. The tool ensures dialogue clarity while maintaining a seamless viewing experience.
from datetime import datetime
import os
import re
import moviepy.editor as mp

print('Starts at: '+datetime.now().strftime("%H:%M:%S"))  
video_path = '1/Friends.S01E14.720p.BluRay.x264.mkv'
subtitle_path = '1/Friends.S01E14.720p.BluRay.x264.srt'
video_extension = os.path.splitext(video_path)[1]
output_video = video_path.replace(video_extension, '-repeated' + video_extension)
subtitle = open(video_path.replace(video_extension, '-repeated.srt'), 'w')
video = mp.VideoFileClip(video_path)

def time_to_ms(time_str):    # Split the time string into components
    hh, mm, ssms = time_str.split(':')
    ss, msmsms = ssms.split(',')
    total_ms = int(hh) * 3600000 + int(mm) * 60000 + int(ss) * 1000 + int(msmsms)    
    return total_ms
def ms_to_time(ms):
    hh = ms // 3600000
    ms %= 3600000
    mm = ms // 60000
    ms %= 60000
    ss = ms // 1000
    ms %= 1000
    time_str = f"{hh:02}:{mm:02}:{ss:02},{ms:03}"    
    return time_str
      
additional = 0        
subtitle_timeframes = []
pattern = r'(\d{2}:\d{2}:\d{2},\d{3}) --> (\d{2}:\d{2}:\d{2},\d{3})'
with open(subtitle_path, 'r') as subtitle_file:
    lines = subtitle_file.readlines()
    for i in range(0, len(lines)):
        match = re.search(pattern, lines[i])
        if match:
            start_time, end_time = match.group(1), match.group(2)
            subtitle_timeframes.append((start_time,end_time))
            subtitle.write(ms_to_time(time_to_ms(start_time)+additional)+' --> ')
            additional+= (time_to_ms(end_time)-time_to_ms(start_time))
            subtitle.write(ms_to_time(time_to_ms(end_time)+additional)+'\n')
        else:
            subtitle.write(lines[i])
print('Timeframes Extracted')            

clips = []
l = '00:00:00,000'
for i in subtitle_timeframes:
	clips.append(video.subclip(l,i[0]))
	clips.append(video.subclip(i[0],i[1]))
	clips.append(video.subclip(i[0],i[1]))
	l = i[1]
	print('clipped upto : '+ms_to_time(time_to_ms(i[1])))
clips.append(video.subclip(l))
repeated_video = mp.concatenate(clips)
print('Concatenated clips')

repeated_video.write_videofile(output_video, codec= 'libx264', fps=video.fps)#change the codec if needed
print(len(clips))
video.close()
subtitle.close()
video.close()
subtitle.close()
print('Successfully created the output file at'+datetime.now().strftime("%H:%M:%S"))

