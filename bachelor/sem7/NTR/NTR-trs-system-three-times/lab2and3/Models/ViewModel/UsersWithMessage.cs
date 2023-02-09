using System.Collections.Generic;
using lab2and3.Models.DomainModel;

namespace lab2and3.Models.ViewModel
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