import imaplib, email, os

user = 'testrfc29@gmail.com'
password = 'Test@123'
imap_url = 'imap.gmail.com'

attachment_dir = 'C:/Users/Tamil Eniyan/Documents/code/Attachments/'

def auth(user,password,imap_url):
    con = imaplib.IMAP4_SSL(imap_url)
    con.login(user,password)
    return con

def get_body(msg):
    if msg.is_multipart():
        return get_body(msg.get_payload(0))
    else:
        return msg.get_payload(None,True)

def get_attachments(msg):
    for part in msg.walk():
        if part.get_content_maintype()=='multipart':
            continue
        if part.get('Content-Disposition') is None:
            continue
        fileName = part.get_filename()

        if bool(fileName):
            filePath = os.path.join(attachment_dir, fileName)
            with open(filePath,'wb') as f:
                f.write(part.get_payload(decode=True))    

def search(key,value,con):
    result, data  = con.search(None,key,'"{}"'.format(value))
    return data

def get_emails(result_bytes):
    msgs = []
    for num in result_bytes[0].split():
        typ, data = con.fetch(num, '(RFC822)')
        msgs.append(data)
    return msgs

con = auth(user,password,imap_url)
con.select('INBOX')

result, data = con.fetch(b'3','(RFC822)')
raw = email.message_from_bytes(data[0][1])
get_attachments(raw)
