package bdlab;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.List;

public class DBTest {
	public static class Contact {
		private int id;

		private String telephoneNumber;

		private String email;
		
		private String website;
		
		private String facebookLink;
		
		
		

		public Contact(int id, String telephoneNumber, String email, String website, String facebookLink) {
			super();
			this.id = id;
			this.telephoneNumber = telephoneNumber;
			this.email = email;
			this.website = website;
			this.facebookLink = facebookLink;
		}
		
		

		public Contact() {
			super();
			// TODO Auto-generated constructor stub
		}
		
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((email == null) ? 0 : email.hashCode());
			result = prime * result + ((facebookLink == null) ? 0 : facebookLink.hashCode());
			result = prime * result + id;
			result = prime * result + ((telephoneNumber == null) ? 0 : telephoneNumber.hashCode());
			result = prime * result + ((website == null) ? 0 : website.hashCode());
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Contact other = (Contact) obj;
			if (email == null) {
				if (other.email != null)
					return false;
			} else if (!email.equals(other.email))
				return false;
			if (facebookLink == null) {
				if (other.facebookLink != null)
					return false;
			} else if (!facebookLink.equals(other.facebookLink))
				return false;
			if (id != other.id)
				return false;
			if (telephoneNumber == null) {
				if (other.telephoneNumber != null)
					return false;
			} else if (!telephoneNumber.equals(other.telephoneNumber))
				return false;
			if (website == null) {
				if (other.website != null)
					return false;
			} else if (!website.equals(other.website))
				return false;
			return true;
		}



		public int getId() {
			return id;
		}

		public void setId(int id) {
			this.id = id;
		}

		public String getTelephoneNumber() {
			return telephoneNumber;
		}

		public void setTelephoneNumber(String telephoneNumber) {
			this.telephoneNumber = telephoneNumber;
		}

		public String getEmail() {
			return email;
		}

		public void setEmail(String email) {
			this.email = email;
		}

		public String getWebsite() {
			return website;
		}

		public void setWebsite(String webiste) {
			this.website = webiste;
		}

		public String getFacebookLink() {
			return facebookLink;
		}

		public void setFacebookLink(String facebookLink) {
			this.facebookLink = facebookLink;
		}

		@Override
		public String toString() {
			return "Person [id=" + id + ", telephoneNumber=" + telephoneNumber + ", email=" + email + ", webiste="
					+ website + ", facebookLink=" + facebookLink + "]";
		}
		

	}

	public final static ResultSetToBean<Contact> contactConverter = new ResultSetToBean<Contact>() {
		public Contact convert(ResultSet rs) throws Exception {
			Contact c = new Contact();
			c.setId(rs.getInt("CONTACT_ID"));
			c.setTelephoneNumber(rs.getString("TELEPHONE_NUMBER"));
			c.setEmail( rs.getString("EMAIL"));
			c.setWebsite( rs.getString("WEBSITE"));
			c.setFacebookLink( rs.getString("FACEBOOK_LINK"));
			return c;
		}
	};
	
	
	//data to insert/update/delete/select
	static String unique_telephone_number = "U-999-998-997";
	static String unique_email = "email_java@bd.pw.edu.pl";
	static String unique_website = "java.bd.pw.edu.pl";
	static String unique_facebook_page = "facebook.com/BD_JAVA";
	
	
	static List<Contact> selectContacts(){
		List<Contact> contacts = DBManager
				.run(new Query() {
					public void prepareQuery(PreparedStatement ps)
							throws Exception {
						ps.setString(1, unique_email);
					}
				}, contactConverter,
						"SELECT * FROM contacts WHERE email = ?");
		return contacts;
	}
	

	
	static void insertContact() {
		DBManager.run(new Task<Boolean>() {
			public Boolean execute(PreparedStatement ps) throws Exception {
				ps.setString(1, unique_telephone_number);
				ps.setString(2, unique_email);
				ps.setString(3, unique_website);
				return ps.executeUpdate() > 0;
			}
		}, "INSERT INTO contacts(telephone_number, email, website) VALUES( ? , ? , ?)");
	}
	
	static void updateContact() {
		DBManager.run(new Task<Boolean>() {
			public Boolean execute(PreparedStatement ps) throws Exception {
				ps.setString(1, unique_facebook_page);
				ps.setString(2, unique_website);
				return ps.executeUpdate() > 0;
			}
		}, "UPDATE contacts SET facebook_link = ? where website = ?");
	}
	
	static void deleteContact() {
		DBManager.run(new Task<Boolean>() {
			public Boolean execute(PreparedStatement ps) throws Exception {
				ps.setString(1, unique_facebook_page);
				return ps.executeUpdate() > 0;
			}
		}, "DELETE FROM contacts WHERE facebook_link = ?");
	}
	
	static void printContacts(List<Contact> contacts) {
		for (Contact c: contacts) {
			System.out.println(c);
		}
	}

	public static void main(String[] args) {

		System.out.println("PRZED WSZYSTKIM:");
		printContacts( selectContacts() );
		
		
		insertContact();
		System.out.println("\nPO INSERCIE:");
		printContacts( selectContacts() );
		
		
		updateContact();		
		System.out.println("\nPO UPDEJCIE:");
		printContacts( selectContacts() );
		
		
		deleteContact();
		System.out.println("\nPO DILICIE- powinno byc to co na poczatku:");
		printContacts( selectContacts() );
	
		
	}

}
