class UTF_HTTPService
{
    RestContext GetContext(string url)
    {
        RestApi api = GetGame().GetRestApi();
        if (!api)
        {
            Print("[UTF_HTTPService] Failed to get RestApi instance.");
            return null;
        }

        RestContext ctx = api.GetContext(url);
        ctx.SetHeader("Accept","application/json");
        if (!ctx)
        {
            Print("[UTF_HTTPService] Failed to create RestContext for URL: " + url);
            return null;
        }
        return ctx;
    }

    void ExecuteGet(string url, ref RestCallback cb)
    {
        RestContext ctx = GetContext(url);
        if (!ctx)
        {
            Print("[UTF_HTTPService] Cannot execute GET request, context is null for URL: " + url);
            return;
        }

        ctx.GET(cb, "get");
    }
};