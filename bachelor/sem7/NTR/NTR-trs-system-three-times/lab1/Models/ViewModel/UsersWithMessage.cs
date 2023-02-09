using System.Collections.Generic;
using lab1.Models.DomainModel;

namespace lab1.Models.ViewModel
{
    public class UsersWithMessage
    {
        public List<User> Users { get; }
        public string Message { get; }

        public UsersWithMessage(List<User> users, string msg)
        {
            Users = users;
            Message = msg;
        }
    }
}