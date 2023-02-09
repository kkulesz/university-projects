using System.Collections.Generic;
using System;

namespace lab1.Models.DomainModel
{
    public class UsersMonth
    {
        public int Year { get; }
        public int Month { get; }
        public string UsersLogin { get; }
        public bool Frozen { get; }

        public UsersMonth(int year, int month, string usersLogin, bool frozen)
        {
            Year = year;
            Month = month;
            UsersLogin = usersLogin;
            Frozen = frozen;
        }

        public DateTime NextMonth()
        {
            if (Month == 12)
                return new DateTime(Year + 1, 1, 1);
            return new DateTime(Year, Month + 1, 1);
        }

        public DateTime PreviousMonth()
        {
            if (Month == 1)
                return new DateTime(Year - 1, 12, 1);
            return new DateTime(Year, Month - 1, 1);
        }

        public DateTime ThisMonth()
        {
            return new DateTime(Year, Month, 1);
        }
    }
}